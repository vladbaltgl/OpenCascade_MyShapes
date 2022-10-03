cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(MainProject CXX)

find_package(OpenCASCADE)

include_directories(SYSTEM ${OpenCASCADE_INCLUDE_DIR})

add_executable(MainProject
main.cpp
Viewer.cpp
Viewer.h
ViewerInterspector.cpp
ViewerInterspector.h
)

foreach(LIB ${OpenCASCADE_LIBRARIES}) 

target_link_libraries(MainProject debug ${OpenCASCADE_LIBRARY_DIR}d/${LIB}.lib)
target_link_libraries(MainProject optimized ${OpenCASCADE_LIBRARY_DIR}/${LIB}.lib)
endforeach()

