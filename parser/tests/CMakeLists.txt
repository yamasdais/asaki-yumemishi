cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Threads REQUIRED)
find_package(GTest REQUIRED)

include(GoogleTest)

file(GLOB srcs test*.cxx)
add_executable(runTest ${srcs})
target_include_directories(runTest
    PRIVATE ${GTEST_INCLUDE_DIR})
target_link_libraries(runTest
    Threads::Threads
    GTest::GTest
    GTest::Main
    )

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

gtest_discover_tests(runTest)