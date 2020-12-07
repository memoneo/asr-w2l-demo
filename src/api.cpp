#include "api.h"
#include "w2l.hpp"

using namespace w2l::helper;

void *loadFiles(const char *acousticModuleFilePath,
                const char *featureModuleFilePath,
                const char *decoderOptionsFilePath,
                const char *tokensFilePath,
                const char *letterFilePath,
                const char *lexiconFilePath,
                const char *languageModelFilePath)
{
    auto acousticModule = loadAcousticModule(acousticModuleFilePath);
    auto featureModule = loadFeatureModule(featureModuleFilePath);
    auto dnnModule = loadDnnModule(acousticModule, featureModule);
    auto decoderOptions = loadDecoderOptions(decoderOptionsFilePath);
    auto tokens = loadTokens(tokensFilePath);
    auto decoderFactory = createDecoderFactory(letterFilePath, lexiconFilePath, languageModelFilePath);

    int nTokens = tokens.size();
    std::cout << "Tokens loaded - " << nTokens << " tokens" << std::endl;

    auto helper = new W2lHelper(dnnModule, decoderFactory, decoderOptions, nTokens);

    return helper;
}

const char *stt(void *w2lHelper, const char *audioFilePath)
{
    auto helper = static_cast<W2lHelper *>(w2lHelper);

    return helper->audioFileToText(audioFilePath).c_str();
}