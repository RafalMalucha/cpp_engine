cmake_minimum_required(VERSION 3.10)
project(cpp_engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Output binaries to build/bin/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

message(STATUS "Toolchain File: ${CMAKE_TOOLCHAIN_FILE}")
message(STATUS "Prefix Path: ${CMAKE_PREFIX_PATH}")

# Options
option(USE_SYSTEM_FMT "Use system-installed fmt library" OFF)
option(USE_SYSTEM_GLM "Use system-installed glm library" OFF)
option(BUILD_TESTS "Build unit tests for cpp_engine" ON)

# FetchContent
include(FetchContent)

# Fix MSVC runtime mismatch for gtest
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# --- Dependencies ---
if(USE_SYSTEM_FMT)
    find_package(fmt CONFIG REQUIRED)
else()
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
    FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 1.0.1
    )
    FetchContent_MakeAvailable(glm)
endif()

if(BUILD_TESTS)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/release-1.12.1.zip
    )
    FetchContent_MakeAvailable(googletest)
endif()

# --- OpenGL ---
find_package(OpenGL REQUIRED)

# --- GLFW ---
add_subdirectory(external/glfw)

# --- GLAD ---
add_library(glad ${CMAKE_SOURCE_DIR}/external/glad/src/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_SOURCE_DIR}/external/glad/include)
target_link_libraries(glad ${CMAKE_DL_LIBS})

# --- STB_IMAGE ---
add_library(stb_image ${CMAKE_SOURCE_DIR}/external/stb_image/stb_image.cpp)
target_include_directories(stb_image PUBLIC ${CMAKE_SOURCE_DIR}/external/stb_image)

# --- TINYGLTF ---
add_library(tiny_gltf ${CMAKE_SOURCE_DIR}/external/tiny_gltf/tiny_gltf.cpp)
target_include_directories(tiny_gltf PUBLIC ${CMAKE_SOURCE_DIR}/external/tiny_gltf)
target_include_directories(tiny_gltf PUBLIC ${CMAKE_SOURCE_DIR}/external/nlohmann)

# --- NLOHMANN JSON ---
target_include_directories(tiny_gltf PUBLIC ${CMAKE_SOURCE_DIR}/external/nlohmann)

# --- Shared library list (platform-specific) ---
if (WIN32)
    set(ENGINE_LIBS glfw glad opengl32 fmt::fmt glm::glm stb_image tiny_gltf)
else()
    set(ENGINE_LIBS glfw glad OpenGL::GL pthread dl fmt::fmt glm::glm stb_image tiny_gltf)
endif()

# --- Main Executable ---
add_executable(cpp_engine
    src/main.cpp
    src/WindowManager.cpp
    src/InputHandler.cpp
    src/Utils.cpp
    src/ShaderLoader.cpp
    src/OpenGLSetup.cpp
    src/Renderer.cpp
    src/Camera.cpp
    src/WindowCallbacks.cpp
    src/Skybox.cpp
    src/Mesh.cpp
    src/Model.cpp
)

target_include_directories(cpp_engine PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/external/glfw/include
    ${CMAKE_SOURCE_DIR}/external/glad/include
    ${CMAKE_SOURCE_DIR}/external/tiny_gltf
    ${CMAKE_SOURCE_DIR}/external/nlohmann
)

target_link_libraries(cpp_engine PRIVATE ${ENGINE_LIBS})

# --- Tests ---
if(BUILD_TESTS)
    enable_testing()

    add_executable(engine_tests
        tests/testUtils.cpp
        tests/testWindowManager.cpp
        src/Utils.cpp
        src/WindowManager.cpp
    )

    target_include_directories(engine_tests PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/external/glfw/include
        ${CMAKE_SOURCE_DIR}/external/glad/include
    )

    target_link_libraries(engine_tests PRIVATE
        gtest_main
        ${ENGINE_LIBS}
    )

    add_test(NAME cpp_engine_tests COMMAND engine_tests)
endif()
