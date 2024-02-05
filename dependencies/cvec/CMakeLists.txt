cmake_minimum_required(VERSION 3.26.4)

project(cvec)

set(CVEC_SOURCES
  source/vec2.c
  source/vec3.c
  source/mat4.c
)

include_directories(include)

add_library(cvec STATIC ${CVEC_SOURCES})

include(CTest)
add_subdirectory(tests)