cmake_minimum_required(VERSION 3.25)
project(BanaRender)

set(CMAKE_CXX_STANDARD 17)

set(EXTERN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/extern")

# assimp
set(BUILD_SHARED_LIBS OFF)
set(ASSIMP_NO_EXPORT ON)
set(ASSIMP_BUILD_TESTS OFF)
set(ASSIMP_INSTALL OFF)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
set(ASSIMP_BUILD_ZLIB ON)

set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT FALSE)
set(ASSIMP_BUILD_OBJ_IMPORTER TRUE)
set(ASSIMP_BUILD_GLTF_IMPORTER TRUE)

add_subdirectory(${EXTERN_DIR}/assimp)

# GLFW
find_package(glfw3 3.3 REQUIRED)

# GLM
find_package(GLM)

include_directories(
        "${EXTERN_DIR}/glad/include"
        "${EXTERN_DIR}/assimp/include"
        "${EXTERN_DIR}/assimp/contrib"
        "${EXTERN_DIR}/imgui"
        "${EXTERN_DIR}/stb/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/core"
)

# main src
file(GLOB MAIN_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core/*.cpp
)

# imgui src
file(GLOB IMGUI_SRC
        ${THIRD_PARTY_DIR}/imgui/imgui/*.cpp
)

add_executable(BanaRender
        main.cpp
        ${MAIN_SRC}
        ${IMGUI_SRC}
)
target_link_libraries(BanaRender PRIVATE
        ${EXTERN}/glad/src/glad.c
        assimp
        glfw
)

# cinolib
set(cinolib_DIR "${EXTERN_DIR}/cinolib")
find_package(cinolib REQUIRED)
add_executable(test test.cpp)
target_link_libraries(test PRIVATE cinolib)