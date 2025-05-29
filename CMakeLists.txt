cmake_minimum_required(VERSION 3.5...4.0)
project(EnigmaSand2 LANGUAGES CXX)

if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  message(WARNING "c++ compiler is not clang, you may run into errors")
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(ENABLE_ASAN "use address sanitizer")
option(ENABLE_MSAN "use memory sanitizer")
option(ENABLE_LSAN "use leak sanitizer")
option(ENABLE_UBSAN "use undefined-behavior sanitizer")

if(ENABLE_ASAN)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
endif()

if(ENABLE_MSAN)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=memory")
endif()

if(ENABLE_LSAN)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak")
endif()

if(ENABLE_UBSAN)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
endif()

add_compile_definitions(
  -D_FORTIFY_SOURCE=3
  -D_GLIBCXX_ASSERTIONS)
add_compile_options(
  -Wall
  -Wextra
  -Wpedantic
  -Werror
  -fno-omit-frame-pointer
  -mno-omit-leaf-frame-pointer
  -fstack-protector-all
  -fstack-clash-protection
  -fcf-protection)
add_link_options(
  -Wl,-z,noexecstack
  -Wl,-z,relro)

find_package(SDL REQUIRED)
find_package(SDL_ttf REQUIRED)

set(PROJECT_SOURCES
  EnigmaSandParticle.cpp
  main.cpp)

add_library(EnigmaSandDeps INTERFACE)
target_include_directories(EnigmaSandDeps INTERFACE
  ${SDL_INCLUDE_DIR}
  ${SDLTTF_INCLUDE_DIR})
target_link_libraries(EnigmaSandDeps INTERFACE
  ${SDL_LIBRARY}
  ${SDLTTF_LIBRARY})

add_library(EnigmaSandStaticAnalyze OBJECT
  ${PROJECT_SOURCES})
target_compile_options(EnigmaSandStaticAnalyze PRIVATE
  --analyze)
target_link_libraries(EnigmaSandStaticAnalyze PRIVATE
  EnigmaSandDeps)

add_executable(EnigmaSand
  ${PROJECT_SOURCES})
target_link_libraries(EnigmaSand PRIVATE
  EnigmaSandDeps)
