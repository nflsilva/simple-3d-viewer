link_libraries(cvec)

add_executable(vec2Tests vec2.c)
add_test(NAME Vec2Tests COMMAND vec2Tests)