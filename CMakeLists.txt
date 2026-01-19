cmake_minimum_required(VERSION 3.10)
project(MyOpenGLApp)

set(CMAKE_CXX_STANDARD 11)

# GLFW
set(GLFW_LIBRARY "$ENV{HOME}/OpenGL/Libraries/GLFW/lib/libglfw3.a")
include_directories($ENV{HOME}/OpenGL/Libraries/GLFW/include)

# GLAD
include_directories(${CMAKE_SOURCE_DIR}/include)

# Build executable with GLAD source
add_executable(my_program 
    src/main.cpp
    src/glad.c
)

target_link_libraries(my_program 
    ${GLFW_LIBRARY}
    "-framework Cocoa"
    "-framework OpenGL" 
    "-framework IOKit"
)