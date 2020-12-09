cmake_minimum_required(VERSION 3.5.1)
cmake_policy(VERSION 3.5.1)

set(project_name w2l) ## rename your project here

project(${project_name})

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" )
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(cereal_INCLUDE_DIRS /root/wav2letter/build/inference/cereal/src/cereal/include)

find_package(Wav2Letter REQUIRED)
find_package(Threads REQUIRED)
find_package(GFlags REQUIRED)
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
  STATIC
  includes/api.h
  src/api.cpp
)

target_include_directories(${project_name}_api PUBLIC ${CMAKE_CURRENT_LIST_DIR}/includes)

target_link_libraries(${project_name}_http
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
  ${project_name}_api
  PUBLIC
    ${project_name}
    streaming_inference_common
    streaming_inference_modules_nn_backend
    streaming_inference_decoder
    streaming_inference_modules_feature
    decoder-library
    Threads::Threads
    wav2letter-inference
    wav2letter-libraries
)

target_link_libraries(
    ${project_name}_http
    PRIVATE
    ${GFLAGS_LIBRARIES_STATIC}
)

set_target_properties(
  ${project_name}
  PROPERTIES
  LINKER_LANGUAGE CXX
  CXX_STANDARD 11
)

set_target_properties(
  ${project_name}_api
  PROPERTIES
  LINKER_LANGUAGE CXX
  CXX_STANDARD 11
)

#target_compile_options(${project_name} PRIVATE -fpie)
#target_compile_options(${project_name}_api PUBLIC -fpie)

#add_dependencies(${project_name}_http ${project_name})
#add_dependencies(${project_name}_api ${project_name})
add_dependencies(${project_name}_api cereal)
add_dependencies(${project_name}_api fbgemm)

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
  ${project_name}_api
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

add_custom_target(combined ALL
   COMMAND ${CMAKE_CXX_ARCHIVE_CREATE} libcombined.a w2l_api streaming_inference_common)