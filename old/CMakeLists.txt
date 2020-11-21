cmake_minimum_required(VERSION 3.5.1)
project(StreamingInferenceExamples)
add_library(StreamingInferenceExamples INTERFACE)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(cereal_INCLUDE_DIRS /root/wav2letter/build/inference/cereal/src/cereal/include)
set(fbgemm_INCLUDE_DIRS 
  /root/wav2letter/build/inference/inference/module/fbgemm/src/fbgemm/include
  /root/wav2letter/build/inference/inference/module/fbgemm/src/fbgemm/third_party/cpuinfo/include)
set(wav2letter-inference_SOURCE_DIR /root/wav2letter/inference)
set(wav2letter++_SOURCE_DIR /root/wav2letter)

add_library(util_example
  ${CMAKE_CURRENT_LIST_DIR}/Util.cpp
)

add_library(wav2letter_inference STATIC IMPORTED) # or STATIC instead of SHARED
set_target_properties(wav2letter_inference PROPERTIES
  IMPORTED_LOCATION "/root/wav2letter/build/inference/libwav2letter-inference.a"
  INTERFACE_INCLUDE_DIRECTORIES "${wav2letter-inference_SOURCE_DIR}"
)

add_library(wav2letter_libraries STATIC IMPORTED) # or STATIC instead of SHARED
set_target_properties(wav2letter_libraries PROPERTIES
  IMPORTED_LOCATION "/root/wav2letter/build/src/libraries/libwav2letter-libraries.a"
  INTERFACE_INCLUDE_DIRECTORIES "/root/wav2letter/src/libraries"
)

include_directories(/root/wav2letter/build/inference)
link_directories(/root/wav2letter/build/inference)

include_directories(${wav2letter-inference_SOURCE_DIR}/inference/common)
link_directories(${wav2letter++_SOURCE_DIR}/build/inference/inference/common)

include_directories(${wav2letter-inference_SOURCE_DIR}/inference/module)
link_directories(${wav2letter++_SOURCE_DIR}/build/inference/inference/module)

find_package(Threads REQUIRED)

target_include_directories(
  util_example
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${cereal_INCLUDE_DIRS}
    ${wav2letter-inference_SOURCE_DIR}
    ${wav2letter++_SOURCE_DIR}/src
)

#add_dependencies(util_example cereal)
#add_dependencies(util_example streaming_inference_common)

target_link_libraries(
  util_example
  PUBLIC
    streaming_inference_common
)

# audio_to_words_example library is used by the example executables
add_library(audio_to_words_example
  ${CMAKE_CURRENT_LIST_DIR}/AudioToWords.cpp
)

target_include_directories(
  audio_to_words_example
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${wav2letter-inference_SOURCE_DIR}
    ${fbgemm_INCLUDE_DIRS}
)

target_link_libraries(
  audio_to_words_example
  PUBLIC
    util_example
    streaming_inference_modules_nn_backend
    streaming_inference_decoder
    decoder-library
    wav2letter_inference
    Threads::Threads
)

function(build_example TARGET SRCFILE)
  message(STATUS "Examples: add executable ${TARGET}")
  add_executable(${TARGET}
    ${SRCFILE}
  )
  add_dependencies(StreamingInferenceExamples ${TARGET})
  target_include_directories(
    ${TARGET}
    PRIVATE
      ${CMAKE_CURRENT_LIST_DIR}
      ${GFLAGS_INCLUDE_DIRS}
  )
  target_link_libraries(
    ${TARGET}
    PRIVATE
      streaming_inference_modules_nn_backend
      streaming_inference_modules_feature
      audio_to_words_example
      ${GFLAGS_LIBRARIES}
  )
endfunction(build_example)

build_example(simple_streaming_asr_example
  ${CMAKE_CURRENT_LIST_DIR}/SimpleStreamingASRExample.cpp)