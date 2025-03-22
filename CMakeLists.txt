cmake_minimum_required(VERSION 3.10)
project(cpp_engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Where to output binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

message(STATUS "Toolchain File: ${CMAKE_TOOLCHAIN_FILE}")
message(STATUS "Prefix Path: ${CMAKE_PREFIX_PATH}")

# Ensure OpenGL is found
find_package(OpenGL REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

# GLFW Setup
add_subdirectory(external/glfw)
include_directories(external/glfw/include)

# GLAD Setup
add_library(glad ${CMAKE_SOURCE_DIR}/external/glad/src/glad.c)
target_include_directories(glad PRIVATE ${CMAKE_SOURCE_DIR}/external/glad/include)
target_link_libraries(glad ${CMAKE_DL_LIBS})

# Define the executable
add_executable(cpp_engine 
    src/main.cpp 
    src/WindowManager.cpp 
    src/InputHandler.cpp 
    src/Utils.cpp
    src/ShaderLoader.cpp
)

# Include directories
target_include_directories(cpp_engine PRIVATE
    ${CMAKE_SOURCE_DIR}/external/glfw/include
    ${CMAKE_SOURCE_DIR}/external/glad/include
)
#target_link_libraries(cpp_engine PRIVATE fmt::fmt)
# Cross-platform linking
if (WIN32)
    target_link_libraries(cpp_engine PRIVATE glfw glad opengl32 fmt::fmt glm::glm)
else()
    target_link_libraries(cpp_engine PRIVATE 
                            glfw 
                            glad 
                            OpenGL::GL 
                            pthread dl
                            fmt::fmt
                            glm::glm)
endif()
