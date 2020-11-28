#include <memory>
#include <string>
#include <vector>

#include "inference/decoder/Decoder.h"
#include "inference/module/module.h"
#include "inference/module/nn/nn.h"
#include "Util.h"

namespace w2l {
namespace inputfiles {
        std::shared_ptr<streaming::Sequential> loadAcousticModule(std::string filePath);
        std::shared_ptr<streaming::Sequential> loadDnnModule(
            std::shared_ptr<streaming::Sequential> featureModule, 
            std::shared_ptr<streaming::Sequential> acousticModule);
        std::shared_ptr<streaming::Sequential> loadFeatureModule(std::string filePath);
        DecoderOptions loadDecoderOptions(std::string filePath);
        std::vector<std::string> loadTokens(std::string filePath);
        std::shared_ptr<const streaming::DecoderFactory> createDecoderFactory(std::string filePath, std::string lexiconFile, std::string languageModelFile);
    }
}

