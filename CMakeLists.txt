cmake_minimum_required(VERSION 3.25)
project(BanaRender)

set(CMAKE_CXX_STANDARD 17)
add_definitions(-DTINYGLTF_IMPLEMENTATION)
add_definitions(-DSTB_IMAGE_IMPLEMENTATION)
add_definitions(-DSTB_IMAGE_WRITE_IMPLEMENTATION)

# GLAD
#add_library(GLAD include/glad/glad.c)
#target_include_directories(GLAD PUBLIC "include/glad")
set(GLAD_C ${PROJECT_SOURCE_DIR}/include/glad/glad.c)
include_directories(include/glad)

# GLFW
find_package(glfw3 3.3 REQUIRED)

# GLM
find_package(GLM)

# tinygltf
add_library(tinygltf INTERFACE)
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
## core
#add_library(BanaCore SHARED
#        src/core/camera.cpp
#        src/core/Mesh.cpp
#        src/core/Model.cpp
#        src/core/Node.cpp
#        src/core/Scene.cpp
#        src/core/Primitive.cpp
#        src/core/shader.cpp
#)
#
#target_link_libraries(BanaCore PUBLIC
#        GLAD
##        tinygltf
#)
#
#target_include_directories(BanaCore
#        PUBLIC
#        #        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
#        #        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/>
#        src/core
#        ${GLM_INCLUDE_DIRS}
#        include/tinygltfT
#)
#
#add_executable(BanaRender main.cpp)
#target_link_libraries(BanaRender PUBLIC
#        BanaCore
#        glfw
#)
#
#add_executable(test test.cpp)
#target_link_libraries(test PUBLIC
#        BanaCore
#        glfw
#)
## GLAD
#set(GLAD_C ${PROJECT_SOURCE_DIR}/src/glad.c)
#
#file (GLOB CORE_FILE core/* )
#
## tinygltf
##file(GLOB TINYGLTF
##        include/tinygltf/*.h
##        include/tinygltf/*.hpp)
#
## GLFW
#find_package(glfw3 3.3 REQUIRED)
#
##  GLM
#find_package(GLM)
#include_directories(
#        ${GLM_INCLUDE_DIRS}
#        ${PROJECT_SOURCE_DIR}/include
#)
#
## tinygltf
#set(TINYGLTF_HEADER_ONLY ON CACHE INTERNAL "" FORCE)
#set(TINYGLTF_INSTALL OFF CACHE INTERNAL "" FORCE)
#add_subdirectory(include/tinygltf)
## tinygltf
##file(GLOB TINYGLTF
##        include/tinygltf/*.h
##        include/tinygltf/*.hpp)
##add_library(tinygltf INTERFACE IMPORTED)
##target_include_directories(tinygltf INTERFACE include/tinygltf)
## 再改下Cmake头文件和.cpp文件的路径分开
#add_library(render_lib SHARED
#        ${GLAD_C}
#        ${CORE_FILE}
#)
#
#target_link_libraries(render_lib PUBLIC
#        glfw
#        tinygltf
#)
#
#target_include_directories(render_lib PUBLIC
#        ${PROJECT_SOURCE_DIR}/include
#)
##target_link_libraries(render_lib PUBLIC
##        tinygltf
##)
#
#add_executable(BanaRender main.cpp)
#target_link_libraries(BanaRender PUBLIC
#        render_lib
#        tinygltf
#)
#
#add_executable(test test.cpp)
#target_link_libraries(test PUBLIC
#        render_lib
#        tinygltf
#)