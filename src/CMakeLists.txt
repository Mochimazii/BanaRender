cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
cmake_policy(VERSION 3.18.0)

project (BanaCore
        VERSION 0.0.1
        LANGUAGES C CXX
)

file(GLOB CORE_FILE core/*.cpp)
file(GLOB TINY_GLTF
        tinygltf/json.hpp
        tinygltf/*.h
)

add_library(BanaCore SHARED
        ${CORE_FILE}
        ${TINY_GLTF}
        ${GLAD_C}
)

target_link_libraries(BanaCore PUBLIC
#        GLAD
#        tinygltf
)

target_include_directories(BanaCore
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
