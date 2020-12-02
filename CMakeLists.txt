cmake_minimum_required(VERSION 3.5.1)

set(project_name w2l) ## rename your project here

project(${project_name})

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" )
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(cereal_INCLUDE_DIRS /root/wav2letter/build/inference/cereal/src/cereal/include)

find_package(Wav2Letter REQUIRED)
find_package(Threads REQUIRED)
find_package(GFLAGS REQUIRED)
find_package(oatpp 1.2.0 REQUIRED)

add_subdirectory(3rdparty)

add_library(${project_name}-lib
  ${CMAKE_CURRENT_LIST_DIR}/src/w2l.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/AudioToWords.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/Util.cpp
)

add_library(${project_name}-api-lib
  src/AppComponent.hpp
  src/controller/Controller.cpp
  src/controller/Controller.hpp
  src/dto/DTOs.hpp
  src/W2lComponent.hpp
  src/service/W2lService.cpp
  src/service/W2lService.hpp
)

target_link_libraries(${project_name}-api-lib
    PUBLIC 
      oatpp::oatpp
      ${project_name}-lib
)

add_executable(${project_name}
  ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
)

target_link_libraries(
  ${project_name}-lib
  PUBLIC
    streaming_inference_common
    streaming_inference_modules_nn_backend
    streaming_inference_decoder
    streaming_inference_modules_feature
    decoder-library
    Threads::Threads
)

target_link_libraries(
    ${project_name}
    PRIVATE
    oatpp::oatpp
    ${project_name}-api-lib
    ${GFLAGS_LIBRARIES}
)

add_dependencies(${project_name} ${project_name}-lib)
add_dependencies(${project_name} ${project_name}-api-lib)

target_include_directories(
  ${project_name}
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/src
)

target_include_directories(
  ${project_name}-lib
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${cereal_INCLUDE_DIRS}
    ${wav2letter-inference_SOURCE_DIR}
    ${wav2letter++_SOURCE_DIR}/src
    3rdparty/base64
    ${GFLAGS_INCLUDE_DIRS}
)

target_include_directories(
  ${project_name}-api-lib
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    src
)