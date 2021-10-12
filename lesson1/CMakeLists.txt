cmake_minimum_required(VERSION 3.18)

project(lesson1 CXX)
add_executable(lesson1 main.cxx)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
target_compile_features(lesson1 PUBLIC cxx_std_17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


#configure_file(${CMAKE_SOURCE_DIR}/data/PhoneBook.txt ${CMAKE_BINARY_DIR}/PhoneBook.txt COPYONLY)



include(CTest)
add_test(NAME chec_lesson1
    COMMAND lesson1)

