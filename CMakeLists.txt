cmake_minimum_required(VERSION 3.10)
project(cpp_engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Where to output binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add GLFW (using the add_subdirectory approach if you've built it in-tree)
add_subdirectory(external/glfw)

# Add GLAD
add_library(glad ${CMAKE_SOURCE_DIR}/external/glad/src/glad.c)
target_include_directories(glad PRIVATE ${CMAKE_SOURCE_DIR}/external/glad/include)
target_link_libraries(glad ${CMAKE_DL_LIBS})

# Add the executable
add_executable(cpp_engine src/main.cpp)

# Link against GLFW, GLAD, and OpenGL
target_link_libraries(cpp_engine glfw glad opengl32)

# Include directories
target_include_directories(cpp_engine PRIVATE
    ${CMAKE_SOURCE_DIR}/external/glfw/include
    ${CMAKE_SOURCE_DIR}/external/glad/include
)