cmake_minimum_required(VERSION 3.22)
project(Penrose)

# Enforce modern C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the packages specified in vcpkg.json
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

# Add your source files here
add_executable(Penrose 
    src/main.cpp
    src/render/Texture.cpp
    src/render/Window.cpp
    src/render/Renderer.cpp
)

target_include_directories(Penrose PRIVATE vendor)
# Link the libraries to your executable
target_link_libraries(Penrose PRIVATE
    glfw
    glad::glad
    glm::glm
)