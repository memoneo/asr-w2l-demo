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

# Util
add_library(util_example
  ${CMAKE_CURRENT_LIST_DIR}/Util.cpp
)
add_dependencies(util_example cereal)
add_dependencies(util_example streaming_inference_common)
target_link_libraries(
  util_example
  PUBLIC
    streaming_inference_common
    decoder-library
)
target_include_directories(
  util_example
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${cereal_INCLUDE_DIRS}
    ${wav2letter-inference_SOURCE_DIR}
    ${wav2letter++_SOURCE_DIR}/src
)


# AudioToWords
add_library(audio_to_words_example
  ${CMAKE_CURRENT_LIST_DIR}/AudioToWords.cpp
)

target_include_directories(
  audio_to_words_example
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    3rdparty/base64
)

target_link_libraries(
  audio_to_words_example
  PUBLIC
    util_example
    streaming_inference_modules_nn_backend
    streaming_inference_decoder
    decoder-library
    Threads::Threads
)

# App
add_executable(w2l_cli ${CMAKE_CURRENT_LIST_DIR}/main.cpp)
target_include_directories(w2l_cli PUBLIC
  ${cereal_INCLUDE_DIRS}
)

target_include_directories(
  w2l_cli
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${GFLAGS_INCLUDE_DIRS}
)
target_link_libraries(
  w2l_cli
  PRIVATE
    streaming_inference_modules_nn_backend
    streaming_inference_modules_feature
    audio_to_words_example
    ${GFLAGS_LIBRARIES}
)