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

add_library(${project_name}
  ${CMAKE_CURRENT_LIST_DIR}/src/w2l.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/AudioToWords.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/Util.cpp
)

add_executable(${project_name}_http
  src/http/AppComponent.hpp
  src/http/controller/Controller.cpp
  src/http/controller/Controller.hpp
  src/http/dto/DTOs.hpp
  src/http/http.cpp
  src/http/W2lComponent.hpp
  src/http/service/W2lService.cpp
  src/http/service/W2lService.hpp
)

add_library(${project_name}_api
  src/api.cpp
  src/api.h
)

target_link_libraries(${project_name}_http
    PUBLIC 
      oatpp::oatpp
      ${project_name}
)

target_link_libraries(${project_name}_api
    PUBLIC 
      oatpp::oatpp
      ${project_name}
)

target_link_libraries(
  ${project_name}
  PUBLIC
    streaming_inference_common
    streaming_inference_modules_nn_backend
    streaming_inference_decoder
    streaming_inference_modules_feature
    decoder-library
    Threads::Threads
)

target_link_libraries(
    ${project_name}_http
    PRIVATE
    oatpp::oatpp
    ${GFLAGS_LIBRARIES}
)

add_dependencies(${project_name}_http ${project_name})
add_dependencies(${project_name}_api ${project_name})

target_include_directories(
  ${project_name}_http
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/src
    ${GFLAGS_INCLUDE_DIRS}
)

target_include_directories(
  ${project_name}
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${cereal_INCLUDE_DIRS}
    ${wav2letter-inference_SOURCE_DIR}
    ${wav2letter++_SOURCE_DIR}/src
)

target_include_directories(
  ${project_name}_http
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    src
)