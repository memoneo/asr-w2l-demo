#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>

#include "inference/module/feature/feature.h"

#include "inference/decoder/Decoder.h"
#include "inference/module/module.h"
#include "inference/module/nn/nn.h"

#include "AudioToWords.h"
#include "Util.h"

using namespace w2l;
using namespace w2l::streaming;

namespace w2l
{
  namespace inputfiles
  {
    std::shared_ptr<streaming::Sequential> loadDnnModule(
        std::shared_ptr<streaming::Sequential> featureModule,
        std::shared_ptr<streaming::Sequential> acousticModule)
    {
      auto dnnModule = std::make_shared<streaming::Sequential>();
      dnnModule->add(featureModule);
      dnnModule->add(acousticModule);

      return dnnModule;
    }

    std::shared_ptr<streaming::Sequential> loadAcousticModule(std::string filePath)
    {
      std::shared_ptr<streaming::Sequential> acousticModule;
      {
        std::ifstream amFile(
            filePath, std::ios::binary);
        if (!amFile.is_open())
        {
          throw std::runtime_error(
              "failed to open acoustic model file=" +
              filePath + " for reading");
        }
        cereal::BinaryInputArchive ar(amFile);
        ar(acousticModule);
      }

      return acousticModule;
    }

    std::shared_ptr<streaming::Sequential> loadFeatureModule(std::string filePath)
    {
      std::shared_ptr<streaming::Sequential> featureModule;

      // Read files
      {
        TimeElapsedReporter feturesLoadingElapsed("features model file loading");
        std::ifstream featFile(
            filePath, std::ios::binary);
        if (!featFile.is_open())
        {
          throw std::runtime_error(
              "failed to open feature file=" +
              filePath + " for reading");
        }
        cereal::BinaryInputArchive ar(featFile);
        ar(featureModule);
      }

      return featureModule;
    }

    DecoderOptions loadDecoderOptions(std::string filePath)
    {
      DecoderOptions decoderOptions;
      {
        TimeElapsedReporter decoderOptionsElapsed("decoder options file loading");
        std::ifstream decoderOptionsFile(
            filePath);
        if (!decoderOptionsFile.is_open())
        {
          throw std::runtime_error(
              "failed to open decoder options file=" +
              filePath + " for reading");
        }
        cereal::JSONInputArchive ar(decoderOptionsFile);
        // TODO: factor out proper serialization functionality or Cereal
        // specialization.
        ar(cereal::make_nvp("beamSize", decoderOptions.beamSize),
           cereal::make_nvp("beamSizeToken", decoderOptions.beamSizeToken),
           cereal::make_nvp("beamThreshold", decoderOptions.beamThreshold),
           cereal::make_nvp("lmWeight", decoderOptions.lmWeight),
           cereal::make_nvp("wordScore", decoderOptions.wordScore),
           cereal::make_nvp("unkScore", decoderOptions.unkScore),
           cereal::make_nvp("silScore", decoderOptions.silScore),
           cereal::make_nvp("eosScore", decoderOptions.eosScore),
           cereal::make_nvp("logAdd", decoderOptions.logAdd),
           cereal::make_nvp("criterionType", decoderOptions.criterionType));
      }

      return decoderOptions;
    }

    std::vector<std::string> loadTokens(std::string filePath)
    {
      std::vector<std::string> tokens;
      {
        std::ifstream tknFile(filePath);
        if (!tknFile.is_open())
        {
          throw std::runtime_error(
              "failed to open tokens file=" +
              filePath + " for reading");
        }
        std::string line;
        while (std::getline(tknFile, line))
        {
          tokens.push_back(line);
        }
      }
      int nTokens = tokens.size();
      std::cout << "Tokens loaded - " << nTokens << " tokens" << std::endl;

      return tokens;
    }

    std::shared_ptr<const DecoderFactory> createDecoderFactory(std::string filePath, std::string lexiconFile, std::string languageModelFile)
    {
      std::vector<float> transitions;

      auto decoderFactory = std::make_shared<DecoderFactory>(
          filePath,
          lexiconFile,
          languageModelFile,
          transitions,
          SmearingMode::MAX,
          "_",
          0);

      return decoderFactory;
    }
  } // namespace inputfiles
} // namespace w2l