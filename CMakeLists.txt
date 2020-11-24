cmake_minimum_required(VERSION 3.5.1)

project(w2l_cli)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" )
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(cereal_INCLUDE_DIRS /root/wav2letter/build/inference/cereal/src/cereal/include)

find_package(Wav2Letter REQUIRED)
find_package(Threads REQUIRED)
find_package(GFLAGS REQUIRED)

add_subdirectory(3rdparty)

add_library(w2l_lib
  ${CMAKE_CURRENT_LIST_DIR}/lib.cpp
  ${CMAKE_CURRENT_LIST_DIR}/AudioToWords.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Util.cpp
)

target_link_libraries(
  w2l_lib
  PUBLIC
    streaming_inference_common
    streaming_inference_modules_nn_backend
    streaming_inference_decoder
    streaming_inference_modules_feature
    decoder-library
    Threads::Threads
)

target_include_directories(
  w2l_lib
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${cereal_INCLUDE_DIRS}
    ${wav2letter-inference_SOURCE_DIR}
    ${wav2letter++_SOURCE_DIR}/src
    3rdparty/base64
)