#include "w2l.hpp"

#ifdef __cplusplus
extern "C" {
#endif
void *loadFiles(const char *acousticModuleFilePath,
                const char *featureModuleFilePath,
                const char *decoderOptionsFilePath,
                const char *tokensFilePath,
                const char *letterFilePath,
                const char *lexiconFilePath,
                const char *languageModelFilePath);

const char *stt(void *w2lHelper, const char *audioFilePath);
#ifdef __cplusplus
}
#endif