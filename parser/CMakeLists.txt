cmake_minimum_required(VERSION 3.10)
project (Parsey CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
# following command needs to be top level CMakeLists.txt
enable_testing()

include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(sample)
add_subdirectory(tests)
