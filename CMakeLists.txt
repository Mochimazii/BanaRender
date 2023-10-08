cmake_minimum_required(VERSION 3.25)
project(BanaRender)

set(CMAKE_CXX_STANDARD 17)


# GLAD
set(GLAD_C ${PROJECT_SOURCE_DIR}/include/glad/glad.c)
include_directories(include/glad)

# GLFW
find_package(glfw3 3.3 REQUIRED)

# GLM
find_package(GLM)

# tinygltf
add_library(tinygltf)
target_sources(tinygltf PRIVATE
       include/tinygltf/tiny_gltf.cpp)
target_include_directories(tinygltf INTERFACE "include/tinygltf")


add_subdirectory(src)

add_executable(BanaRender main.cpp)
target_link_libraries(BanaRender PRIVATE
        BanaCore
        glfw
)

add_executable(test test.cpp)
target_link_libraries(test PRIVATE
        BanaCore
        glfw
)