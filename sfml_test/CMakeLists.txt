cmake_minimum_required(VERSION 3.10)
project(sfml_test)

set(CMAKE_CXX_STANDARD 17)

set(SFML_DIR "D:/SFML/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

include_directories(${SFML_INCLUDE_DIR})

add_executable(sfml_test src/main.cpp)

target_link_libraries(sfml_test sfml-graphics sfml-window sfml-system)
