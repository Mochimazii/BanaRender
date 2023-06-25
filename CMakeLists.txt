cmake_minimum_required(VERSION 3.25)
project(BanaRender)

set(CMAKE_CXX_STANDARD 17)

# GLAD
include_directories(${PROJECT_SOURCE_DIR}/include)
set(GLAD_C ${PROJECT_SOURCE_DIR}/src/glad.c)

file (GLOB CORE_FILE core/* )

# image IO
file(GLOB IMAGE_IO include/stb_image/*.h
        IMAGE_IO include/stb_image/*.cpp
        )

add_library(render_lib ${GLAD_C}
        ${CORE_FILE}
        ${IMAGE_IO}
        )

add_executable(BanaRender main.cpp
#        ${GLAD_C}
#        ${CORE_FILE}
#        ${IMAGE_IO}
        )

target_link_libraries(BanaRender render_lib)

# GLFW
find_package(glfw3 3.3 REQUIRED)
target_link_libraries(BanaRender glfw)

#  GLM
find_package(GLM)
include_directories(${GLM_INCLUDE_DIRS})