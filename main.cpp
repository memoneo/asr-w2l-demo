#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include <gflags/gflags.h>
#include "rpc/server.h"

#include "AudioToWords.h"
#include "w2l.h"

using namespace w2l;
using namespace w2l::streaming;
using namespace w2l::inputfiles;

DEFINE_string(
    input_files_base_path,
    "./model",
    "path is added as prefix to input files unless the input file"
    " is a full path.");
DEFINE_string(
    feature_module_file,
    "feature_extractor.bin",
    "serialized feature extraction module.");
DEFINE_string(
    acoustic_module_file,
    "acoustic_model.bin",
    "binary file containing acoustic module parameters.");
DEFINE_string(
    transitions_file,
    "",
    "binary file containing ASG criterion transition parameters.");
DEFINE_string(tokens_file, "tokens.txt", "text file containing tokens.");
DEFINE_string(lexicon_file, "lexicon.txt", "text file containing lexicon.");
DEFINE_string(
    input_audio_file,
    "",
    "16KHz wav audio input file to be traslated to words. "
    "If no file is specified then it is read of standard input.");
DEFINE_string(silence_token, "_", "the token to use to denote silence");
DEFINE_string(
    language_model_file,
    "language_model.bin",
    "binary file containing language module parameters.");
DEFINE_string(
    decoder_options_file,
    "decoder_options.json",
    "JSON file containing decoder options"
    " including: max overall beam size, max beam for token selection, beam score threshold"
    ", language model weight, word insertion score, unknown word insertion score"
    ", silence insertion score, and use logadd when merging decoder nodes");

std::string GetInputFileFullPath(const std::string &fileName)
{
    return GetFullPath(fileName, FLAGS_input_files_base_path);
}

int main(int argc, char *argv[])
{
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    auto acousticModule = loadAcousticModule(FLAGS_acoustic_module_file);
    auto featureModule = loadFeatureModule(FLAGS_feature_module_file);
    auto dnnModule = loadDnnModule(featureModule, acousticModule);
    auto decoderOptions = loadDecoderOptions(FLAGS_decoder_options_file);
    auto tokens = loadTokens(FLAGS_tokens_file);
    auto decoderFactory = createDecoderFactory(FLAGS_tokens_file, FLAGS_lexicon_file, FLAGS_language_model_file);

    int nTokens = tokens.size();
    std::cout << "Tokens loaded - " << nTokens << " tokens" << std::endl;

    rpc::server srv(8080);

    srv.bind("transcribe", [&](std::string base64EncodedAudio) {
        //audioFileToWordsString("test", dnnModule, decoderFactory, decoderOptions, nTokens);

        return "swigswag";
    });

    srv.run();

    return 0;
}
