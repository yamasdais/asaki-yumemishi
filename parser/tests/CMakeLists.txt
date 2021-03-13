cmake_minimum_required(VERSION 3.9)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()
find_package(Threads REQUIRED)

include(GoogleTest)

add_executable(GTest test_Error.cxx)
target_include_directories(GTest
    PRIVATE ${GTEST_INCLUDE_DIR})
target_link_libraries(GTest
    PRIVATE Threads::Threads
    PRIVATE ${GTEST_LIBRARY}
    PRIVATE ${GTEST_MAIN_LIBRARY}
    )

gtest_discover_tests(GTest)