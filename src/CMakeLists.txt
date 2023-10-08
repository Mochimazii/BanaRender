cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
cmake_policy(VERSION 3.18.0)

project (BanaCore
        VERSION 0.0.1
        LANGUAGES C CXX
)

file(GLOB CORE_FILE core/*.cpp)

add_library(BanaCore
        ${CORE_FILE}
        ${GLAD_C}
)

target_link_libraries(BanaCore PUBLIC
        tinygltf
)

target_include_directories(BanaCore
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
