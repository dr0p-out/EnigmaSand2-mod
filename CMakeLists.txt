cmake_minimum_required(VERSION 3.5...4.0)
project(EnigmaSand2 LANGUAGES CXX)

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

add_compile_options(
  -Wall
  -Wextra
  -Wpedantic
  -Werror)

find_package(SDL REQUIRED)
find_package(SDL_ttf REQUIRED)

add_executable(EnigmaSand
  EnigmaSandParticle.cpp
  main.cpp)
target_include_directories(EnigmaSand PRIVATE
  ${SDL_INCLUDE_DIR}
  ${SDLTTF_INCLUDE_DIR})
target_link_libraries(EnigmaSand PRIVATE
  ${SDL_LIBRARY}
  ${SDLTTF_LIBRARY})
