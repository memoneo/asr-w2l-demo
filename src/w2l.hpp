#pragma once
#include <memory>
#include <string>
#include <vector>

#include "inference/decoder/Decoder.h"
#include "inference/module/module.h"
#include "inference/module/nn/nn.h"
#include "Util.hpp"

namespace w2l
{
    namespace helper
    {
        class W2lHelper
        {
            std::shared_ptr<streaming::Sequential> dnnModule;
            std::shared_ptr<const streaming::DecoderFactory> decoderFactory;
            DecoderOptions decoderOptions;
            int nTokens;

        public:
            /**
             * Constructor with object mapper.
             * @param objectMapper - default object mapper used to serialize/deserialize DTOs.
             */
            W2lHelper(std::shared_ptr<streaming::Sequential> dnnModule,
                      std::shared_ptr<const streaming::DecoderFactory> decoderFactory,
                      DecoderOptions decoderOptions,
                      int nTokens)
            {
                this->dnnModule = dnnModule;
                this->decoderFactory = decoderFactory;
                this->decoderOptions = decoderOptions;
                this->nTokens = nTokens;
            }
            std::string audioFileToText(std::string filePath);
        };

        std::shared_ptr<streaming::Sequential> loadAcousticModule(std::string filePath);
        std::shared_ptr<streaming::Sequential> loadDnnModule(
            std::shared_ptr<streaming::Sequential> featureModule,
            std::shared_ptr<streaming::Sequential> acousticModule);
        std::shared_ptr<streaming::Sequential> loadFeatureModule(std::string filePath);
        DecoderOptions loadDecoderOptions(std::string filePath);
        std::vector<std::string> loadTokens(std::string filePath);
        std::shared_ptr<const streaming::DecoderFactory> createDecoderFactory(std::string filePath, std::string lexiconFile, std::string languageModelFile);
    } // namespace inputfiles
} // namespace w2l
