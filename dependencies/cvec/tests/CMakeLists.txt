find_library(MATH_LIBRARY m)

link_libraries(cvec ${MATH_LIBRARY})

add_executable(vec2Tests vec2.c)
add_test(NAME Vec2Tests COMMAND vec2Tests)

add_executable(vec3Tests vec3.c)
add_test(NAME Vec3Tests COMMAND vec3Tests)

add_executable(mat4Tests mat4.c)
add_test(NAME Mat4Tests COMMAND mat4Tests)