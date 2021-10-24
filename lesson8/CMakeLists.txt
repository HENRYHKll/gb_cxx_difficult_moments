cmake_minimum_required(VERSION 3.18)

project(lesson8)

set(CMAKE_CXX_STANDARD 17)

# Build googletest
add_subdirectory(
    "${CMAKE_CURRENT_SOURCE_DIR}/googletest" 
    "googletest"
)

# Main target
add_executable(
    lesson8
    src/main.cxx
    src/lesson1.hxx
)

# Test target
add_executable(
    test_lesson8
    test/test_lesson1.cxx
)

# Add src to the include directories for the test target
target_include_directories(
    test_lesson8 PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

# Link test target against gtest libraries
target_link_libraries(
    test_lesson8 PRIVATE
    gtest gtest_main
)

#configure_file(${CMAKE_SOURCE_DIR}/data/PhoneBook.txt ${CMAKE_BINARY_DIR}/PhoneBook.txt COPYONLY)


if (MSVC)
    # @see https://github.com/google/googletest/blob/master/googletest/README.md
    # Visual Studio Dynamic vs Static Runtimes
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    target_compile_options(
        lesson8 PRIVATE
        /W4
    )
    target_compile_options(
        test_lesson8 PRIVATE
        /W4
    )
else ()
    target_compile_options(
        lesson8 PRIVATE

    )
    target_compile_options(
        test_lesson8 PRIVATE

    )
endif()
