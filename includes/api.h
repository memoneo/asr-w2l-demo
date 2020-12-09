#ifdef __cplusplus
extern "C" {
#endif
const void *loadHelper(const char *acousticModuleFilePath,
                const char *featureModuleFilePath,
                const char *decoderOptionsFilePath,
                const char *tokensFilePath,
                const char *letterFilePath,
                const char *lexiconFilePath,
                const char *languageModelFilePath);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#endif
const char *stt(void *w2lHelper, const char *audioFilePath);
#ifdef __cplusplus
}
#endif