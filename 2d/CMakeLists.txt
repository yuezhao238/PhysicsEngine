cmake_minimum_required(VERSION 3.10)
project(2d)

set(CMAKE_CXX_STANDARD 17)

set(SFML_STATIC_LIBRARIES TRUE)
add_definitions(-DSFML_STATIC)
set(SFML_DIR "D:/SFML/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

include_directories(include ${SFML_INCLUDE_DIR})

add_executable(2d src/main.cpp src/physics_engine.cpp)

target_link_libraries(2d sfml-graphics sfml-window sfml-system opengl32 winmm gdi32)
