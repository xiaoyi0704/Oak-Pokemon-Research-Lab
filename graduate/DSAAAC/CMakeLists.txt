cmake_minimum_required(VERSION 3.6)
project(DataStructures)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-O0")
if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
else()
    message(WARNING "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif()
add_subdirectory(chapter3)
add_subdirectory(chapter4)
add_subdirectory(chapter5)
add_subdirectory(chapter6)
add_executable(main main.c)
target_link_libraries(main ${CONAN_LIBS})