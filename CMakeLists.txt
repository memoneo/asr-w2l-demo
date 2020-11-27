cmake_minimum_required(VERSION 3.5.1)

project(w2l_cli)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" )
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(cereal_INCLUDE_DIRS /root/wav2letter/build/inference/cereal/src/cereal/include)

find_package(Wav2Letter REQUIRED)
find_package(Threads REQUIRED)
find_package(GFLAGS REQUIRED)
find_package(Drogon CONFIG REQUIRED)

add_subdirectory(3rdparty)

add_library(w2l_lib
  ${CMAKE_CURRENT_LIST_DIR}/w2l.cpp
  ${CMAKE_CURRENT_LIST_DIR}/AudioToWords.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Util.cpp
)

add_executable(w2l
  ${CMAKE_CURRENT_LIST_DIR}/main.cpp
  ${CMAKE_CURRENT_LIST_DIR}/AudioToWords.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Util.cpp
)

if(CMAKE_CXX_STANDARD LESS 17)
  message(STATUS "use c++14")
  find_package(Boost 1.61.0 REQUIRED)
  target_include_directories(w2l PRIVATE ${Boost_INCLUDE_DIRS})
else()
  message(STATUS "use c++17")
endif()


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

target_link_libraries(
    w2l
    PRIVATE
    w2l_lib
    Drogon::Drogon
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