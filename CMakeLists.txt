cmake_minimum_required(VERSION 3.25)
project(BanaRender)

set(CMAKE_CXX_STANDARD 17)
add_definitions(-DTINYGLTF_IMPLEMENTATION)
add_definitions(-DSTB_IMAGE_IMPLEMENTATION)
add_definitions(-DSTB_IMAGE_WRITE_IMPLEMENTATION)

# GLAD
include_directories(${PROJECT_SOURCE_DIR}/include)
set(GLAD_C ${PROJECT_SOURCE_DIR}/src/glad.c)

file (GLOB CORE_FILE core/* )

# image IO
file(GLOB IMAGE_IO
        include/stb_image/*.h
        include/stb_image/*.cpp)

# tinygltf
file(GLOB TINYGLTF
        include/tinygltf/*.h
        include/tinygltf/*.hpp)

add_library(render_lib ${GLAD_C}
        ${CORE_FILE}
        ${IMAGE_IO}
        ${TINYGLTF}
)

add_executable(BanaRender main.cpp)
target_link_libraries(BanaRender render_lib)

add_executable(test test.cpp)
target_link_libraries(test render_lib)

# GLFW
find_package(glfw3 3.3 REQUIRED)
target_link_libraries(BanaRender glfw)

#  GLM
find_package(GLM)
include_directories(${GLM_INCLUDE_DIRS})
