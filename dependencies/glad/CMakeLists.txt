cmake_minimum_required(VERSION 3.26.4)

set(GLAD_SOURCES
  src/glad.c
)

include_directories(include)
add_library(glad STATIC ${GLAD_SOURCES})