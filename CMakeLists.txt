cmake_minimum_required(VERSION 3.26.4)

set(TARGET_NAME s3v)
project(${TARGET_NAME})
add_compile_options(-Wall -Wextra)

file(GLOB_RECURSE S3V_SOURCES source/*.c)

set(GLFW_BUILD_EXAMPLES false)
set(GLFW_BUILD_TESTS false)
find_package(OpenGL REQUIRED)

add_subdirectory(dependencies/glad)
add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/cutil)
add_subdirectory(dependencies/cvec)

# Add ImGui sources
set(IMGUI_SOURCES
    dependencies/imgui/imgui.cpp
    dependencies/imgui/imgui_demo.cpp
    dependencies/imgui/imgui_draw.cpp
    dependencies/imgui/imgui_widgets.cpp
    dependencies/imgui/backends/imgui_impl_glfw.cpp
    dependencies/imgui/backends/imgui_impl_opengl3.cpp
)

set(IMGUI_INCLUIDE_DIRS
    dependencies/imgui
    dependencies/imgui/backends
)

set(
    S3V_INCLUDE_DIRS
    include
    ${OPENGL_INCLUDE_DIRS}
    dependencies/glad/include
    dependencies/glfw/include
    dependencies/cutil/include
    dependencies/cvec/include
    dependencies/nuklear
)

set(
    S3V_LIBRARIES
    ${OPENGL_LIBRARIES}
    glad
    glfw
    cutil
    cvec
)

add_executable(${TARGET_NAME} ${S3V_SOURCES})
target_include_directories(${TARGET_NAME} PRIVATE ${S3V_INCLUDE_DIRS})
target_link_libraries(${TARGET_NAME} ${S3V_LIBRARIES})
