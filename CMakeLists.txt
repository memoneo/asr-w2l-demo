cmake_minimum_required(VERSION 3.5.1)

project(w2l_cli)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" )
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(cereal_INCLUDE_DIRS /root/wav2letter/build/inference/cereal/src/cereal/include)

find_package(Wav2Letter REQUIRED)

add_executable(w2l_cli main.cpp)

add_subdirectory(3rdparty)

target_include_directories(
    w2l_cli
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${cereal_INCLUDE_DIRS}
        ${WAV2LETTER_INCLUDE_DIRS}
)

target_link_libraries(w2l_cli
  wav2letter-inference
)