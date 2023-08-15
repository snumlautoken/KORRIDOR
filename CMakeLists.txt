cmake_minimum_required (VERSION 3.11)
project (KORRIDOR)

set (CMAKE_CXX_STANDARD 20)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

set(CMAKE_BUILD_TYPE Debug)
add_executable (KORRIDOR src/main.cpp src/graphics.cpp src/prism.cpp src/shader.cpp src/input.cpp)
target_link_libraries(KORRIDOR glfw OpenGL GLEW)
