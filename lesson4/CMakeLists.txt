cmake_minimum_required(VERSION 3.18)

project(lesson4 CXX)
add_executable(lesson4 main.cxx)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
target_compile_features(lesson4 PUBLIC cxx_std_17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)



include(CTest)
add_test(NAME chec_lesson4
    COMMAND lesson4)

