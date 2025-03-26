cmake_minimum_required(VERSION 3.10)
project(raytracer)

# Set C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenMP if available
find_package(OpenMP)

# Add stb_image_write header location
include_directories(${CMAKE_SOURCE_DIR}/external/stb)

# Source files
set(SOURCES
    src/main.cpp
    src/scene.cpp
    src/renderer.cpp
    src/material.cpp
    src/camera.cpp
    src/vec3.cpp
)

# Create executable
add_executable(ray_tracer ${SOURCES})

# Add OpenMP flags if found
if(OpenMP_CXX_FOUND)
    target_link_libraries(ray_tracer PUBLIC OpenMP::OpenMP_CXX)
endif()

# Include directories
target_include_directories(ray_tracer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
