cmake_minimum_required(VERSION 3.5...4.0)
project(EnigmaSand2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(
  -Wall
  -Wextra
  -Wpedantic
  -Werror)

find_package(SDL REQUIRED)
find_package(SDL_ttf REQUIRED)

add_executable(EnigmaSand
  main.cpp)
target_include_directories(EnigmaSand PRIVATE
  ${SDL_INCLUDE_DIR}
  ${SDLTTF_INCLUDE_DIR})
target_link_libraries(EnigmaSand PRIVATE
  ${SDL_LIBRARY}
  ${SDLTTF_LIBRARY})
