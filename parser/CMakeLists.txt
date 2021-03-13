cmake_minimum_required(VERSION 3.10)
project (Parsey CXX)

include(ExternalProject)
SET_DIRECTORY_PROPERTIES(PROPERTIES EP_PREFIX ${PROJECT_SOURCE_DIR}/external)
externalproject_add(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest
    GIT_TAG release-1.10.0
    #URL https://github.com/google/googletest/archive/release-1.10.0.zip
    UPDATE_COMMAND "" # skip update command
    INSTALL_COMMAND "" # skip install step
    SOURCE_DIR ${PROJECT_SOURCE_DIR}/external/googletest
    BINARY_DIR ${PROJECT_SOURCE_DIR}/external/googletest/build
    BUILD_COMMAND cmake ..
    )

externalproject_get_property(googletest source_dir)
set(GTEST_INCLUDE_DIR ${source_dir}/googletest/include)
set(GMOCK_INCLUDE_DIR ${source_dir}/googlemock/include)
externalproject_get_property(googletest binary_dir)
set(GTEST_MAIN_LIBRARY ${binary_dir}/lib/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main.a) # in Unix, libgtest.a
set(GTEST_LIBRARY ${binary_dir}/lib/${CMAKE_FIND_LIBRARY_PREFIXES}gtest.a)
#add_library(${GTEST_LIBRARY} UNKNOWN IMPORTED)
#set_target_properties(${GTEST_LIBRARY} PROPERTIES
#  IMPORTED_LOCATION ${GTEST_MAIN_LIBRARY}
#  INTERFACE_LINK_LIBRARIES Threads::Threads)
#add_dependencies(${GTEST_LIBRARY} googletest)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(sample)
add_subdirectory(tests)
