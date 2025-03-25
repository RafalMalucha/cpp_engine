cmake_minimum_required(VERSION 3.10)
project(cpp_engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Where to output binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

message(STATUS "Toolchain File: ${CMAKE_TOOLCHAIN_FILE}")
message(STATUS "Prefix Path: ${CMAKE_PREFIX_PATH}")

option(USE_SYSTEM_FMT "Use system-installed fmt library" OFF)

option(USE_SYSTEM_GLM "Use system-installed glm library" OFF)

# Ensure OpenGL is found
find_package(OpenGL REQUIRED)

if(USE_SYSTEM_FMT)
    find_package(fmt CONFIG REQUIRED)
else()
    include(FetchContent)
    FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 10.2.1
    )
    FetchContent_MakeAvailable(fmt)
endif()

if(USE_SYSTEM_GLM)
    find_package(glm CONFIG REQUIRED)
else()
    include(FetchContent)
    FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 1.0.1
    )
    FetchContent_MakeAvailable(glm)
endif()

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
