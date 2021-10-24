cmake_minimum_required(VERSION 3.18)

project(lesson5 CXX)
add_executable(lesson5 main.cxx)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
target_compile_features(lesson5 PUBLIC cxx_std_17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)



include(CTest)
add_test(NAME chec_lesson5
    COMMAND lesson5)

