cmake_minimum_required(VERSION 3.10)

project(lesson7 CXX)
add_executable(lesson7 main.cxx studentLib.pb.h)

include(FindProtobuf)
find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
target_compile_features(lesson7 PUBLIC cxx_std_17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)



include(CTest)
add_test(NAME chec_lesson7
    COMMAND lesson7)

