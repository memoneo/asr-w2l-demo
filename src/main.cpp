#include <fstream>
#include <memory>
#include <string>
#include <vector>
#include "oatpp/network/Server.hpp"

#include <iostream>
#include <gflags/gflags.h>

#include "./controller/Controller.hpp"
#include "./AppComponent.hpp"

#include "AudioToWords.h"
#include "w2l.h"

using namespace w2l;
using namespace w2l::streaming;
using namespace w2l::inputfiles;
using namespace oatpp;

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

void run() {

  /* Register Components in scope of run() method */
  AppComponent components;

  /* Get router component */
  OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);

  /* Create MyController and add all of its endpoints to router */
  auto controller = std::make_shared<Controller>();
  controller->addEndpointsToRouter(router);

  /* Get connection handler component */
  OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler);

  /* Get connection provider component */
  OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider);

  /* Create server which takes provided TCP connections and passes them to HTTP connection handler */
  oatpp::network::Server server(connectionProvider, connectionHandler);

  /* Priny info about server port */
  OATPP_LOGI("w2l-api", "Server running on port %s", connectionProvider->getProperty("port").getData());

  /* Run server */
  server.run();
}

int main(int argc, char *argv[])
{
    gflags::ParseCommandLineFlags(&argc, &argv, true);

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

    oatpp::base::Environment::init();

    run();
    
    /* Print how much objects were created during app running, and what have left-probably leaked */
    /* Disable object counting for release builds using '-D OATPP_DISABLE_ENV_OBJECT_COUNTERS' flag for better performance */
    std::cout << "\nEnvironment:\n";
    std::cout << "objectsCount = " << oatpp::base::Environment::getObjectsCount() << "\n";
    std::cout << "objectsCreated = " << oatpp::base::Environment::getObjectsCreated() << "\n\n";
    
    oatpp::base::Environment::destroy();

    return 0;
}