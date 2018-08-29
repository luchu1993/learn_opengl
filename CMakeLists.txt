cmake_minimum_required(VERSION 2.10)

project(learn_opengl)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_BUILD_TYPE "Debug")

include_directories(glad/include include)

add_executable(hello_window src/hello_window.cpp glad/src/glad.c)
add_executable(glm_test src/glm_test.cpp)
add_executable(lighting src/lighting.cpp glad/src/glad.c)

target_link_libraries(hello_window GL dl glfw)
target_link_libraries(lighting GL dl glfw SOIL)
