cmake_minimum_required(VERSION 3.10)

project(goclient)

include_directories(JNI include)

set(SOURCES
    # Entry of the dll ofc
    entry/dllmain.cpp

    # Client entry
    src/client.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR})
add_library(goclient SHARED ${SOURCES})
target_link_libraries(goclient ${CMAKE_SOURCE_DIR}/libs/jawt.lib ${CMAKE_SOURCE_DIR}/libs/jvm.lib)