#include <memory>
#include <string>
#include <vector>

#include "inference/decoder/Decoder.h"
#include "inference/module/module.h"
#include "inference/module/nn/nn.h"
#include "Util.h"

namespace w2l {
namespace streaming {
        std::shared_ptr<streaming::Sequential> loadAcousticModule(std::string fileName);
        std::shared_ptr<streaming::Sequential> loadDnnModule(
            std::shared_ptr<streaming::Sequential> featureModule, 
            std::shared_ptr<streaming::Sequential> acousticModule);
        std::shared_ptr<streaming::Sequential> loadFeatureModule(std::string fileName);
        DecoderOptions loadDecoderOptions(std::string fileName);
        std::vector<std::string> loadTokens(std::string fileName);
        std::shared_ptr<const DecoderFactory> createDecoderFactory(std::string fileName, std::string lexiconFile, std::string languageModelFile);
    }
}

