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

int main(int argc, char* argv[]) {
  return 0;
}

std::string GetInputFileFullPath(const std::string& fileName) {
  return GetFullPath(fileName, ".");
}

std::shared_ptr<streaming::Sequential> loadDnnModule(
  std::shared_ptr<streaming::Sequential> featureModule, 
  std::shared_ptr<streaming::Sequential> acousticModule) {
  auto dnnModule = std::make_shared<streaming::Sequential>();
  dnnModule->add(featureModule);
  dnnModule->add(acousticModule);

  return dnnModule;
}

std::shared_ptr<streaming::Sequential> loadAcousticModule(std::string fileName) {
  std::shared_ptr<streaming::Sequential> acousticModule;
  {
    std::ifstream amFile(
        GetInputFileFullPath(fileName), std::ios::binary);
    if (!amFile.is_open()) {
      throw std::runtime_error(
          "failed to open acoustic model file=" +
          GetInputFileFullPath(fileName) + " for reading");
    }
    cereal::BinaryInputArchive ar(amFile);
    ar(acousticModule);
  }

  return acousticModule;
}

std::shared_ptr<streaming::Sequential> loadFeatureModule(std::string fileName) {
  std::shared_ptr<streaming::Sequential> featureModule;

  // Read files
  {
    TimeElapsedReporter feturesLoadingElapsed("features model file loading");
    std::ifstream featFile(
        GetInputFileFullPath(fileName), std::ios::binary);
    if (!featFile.is_open()) {
      throw std::runtime_error(
          "failed to open feature file=" +
          GetInputFileFullPath(fileName) + " for reading");
    }
    cereal::BinaryInputArchive ar(featFile);
    ar(featureModule);
  }

  return featureModule;
}

DecoderOptions loadDecoderOptions(std::string fileName) {
  DecoderOptions decoderOptions;
  {
    TimeElapsedReporter decoderOptionsElapsed("decoder options file loading");
    std::ifstream decoderOptionsFile(
        GetInputFileFullPath(fileName));
    if (!decoderOptionsFile.is_open()) {
      throw std::runtime_error(
          "failed to open decoder options file=" +
          GetInputFileFullPath(fileName) + " for reading");
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

std::vector<std::string> loadTokens(std::string fileName) {
  std::vector<std::string> tokens;
  {
    std::ifstream tknFile(GetInputFileFullPath(fileName));
    if (!tknFile.is_open()) {
      throw std::runtime_error(
          "failed to open tokens file=" +
          GetInputFileFullPath(fileName) + " for reading");
    }
    std::string line;
    while (std::getline(tknFile, line)) {
      tokens.push_back(line);
    }
  }
  int nTokens = tokens.size();
  std::cout << "Tokens loaded - " << nTokens << " tokens" << std::endl;

  return tokens;
}

std::shared_ptr<const DecoderFactory> createDecoderFactory(std::string fileName, std::string lexiconFile, std::string languageModelFile) {
    std::vector<float> transitions;

    auto decoderFactory = std::make_shared<DecoderFactory>(
        GetInputFileFullPath(fileName),
        GetInputFileFullPath(lexiconFile),
        GetInputFileFullPath(languageModelFile),
        transitions,
        SmearingMode::MAX,
        "_",
        0);

    return decoderFactory;
}
