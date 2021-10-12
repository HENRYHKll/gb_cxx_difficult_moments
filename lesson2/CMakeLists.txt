cmake_minimum_required(VERSION 3.18)

project(lesson2 CXX)
add_executable(lesson2 main.cxx)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
target_compile_features(lesson2 PUBLIC cxx_std_17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


#configure_file(${CMAKE_SOURCE_DIR}/data/War-and-peace.txt ${CMAKE_BINARY_DIR}/War-and-peace.txt COPYONLY)



include(CTest)
add_test(NAME chec_lesson2
    COMMAND lesson2)

