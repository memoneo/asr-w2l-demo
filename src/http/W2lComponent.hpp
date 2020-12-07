

#ifndef W2LCOMPONENT_HPP
#define W2LCOMPONENT_HPP

#include "w2l.hpp"
#include <gflags/gflags.h>
#include "Util.hpp"
#include "oatpp/core/macro/component.hpp"

#include <iostream>

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

using namespace w2l::helper;
using namespace w2l::streaming;

std::string GetInputFileFullPath(const std::string &fileName)
{
    return GetFullPath(fileName, FLAGS_input_files_base_path);
}

class W2lComponent {
public:

  OATPP_CREATE_COMPONENT(std::shared_ptr<W2lHelper>, w2lHelper)([] {

    auto acousticModule = loadAcousticModule(GetInputFileFullPath(FLAGS_acoustic_module_file));
    auto featureModule = loadFeatureModule(GetInputFileFullPath(FLAGS_feature_module_file));
    auto dnnModule = loadDnnModule(featureModule, acousticModule);
    auto decoderOptions = loadDecoderOptions(GetInputFileFullPath(FLAGS_decoder_options_file));
    auto tokens = loadTokens(GetInputFileFullPath(FLAGS_tokens_file));
    auto decoderFactory = createDecoderFactory(GetInputFileFullPath(FLAGS_tokens_file), 
        GetInputFileFullPath(FLAGS_lexicon_file), 
        GetInputFileFullPath(FLAGS_language_model_file));

    int nTokens = tokens.size();
    std::cout << "Tokens loaded - " << nTokens << " tokens" << std::endl;

    return std::make_shared<W2lHelper>(dnnModule, decoderFactory, decoderOptions, nTokens);

  }());


};

#endif //CRUD_DATABASECOMPONENT_HPP