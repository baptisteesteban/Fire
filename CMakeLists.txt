cmake_minimum_required(VERSION 3.10)
project(fire CXX)

set(OpenGL_GL_PREFERENCE LEGACY)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${SDL2_DIR})

set(CMAKE_CXX_STANDARD 17)

set(SRC
  src/main.cc
  src/program.cc
  src/triangle.cc)

add_executable(fire ${SRC})
target_link_libraries(fire OpenGL::GL SDL2::SDL2 SDL2::SDL2main GLEW)
