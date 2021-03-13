cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)


macro(make_execs)
    file(GLOB srcs sample*.cxx)
    foreach(src IN LISTS srcs)
        get_filename_component(exe ${src} NAME_WE)
        message("SRC: " ${src} ", exe:" ${exe})
        add_executable(${exe} ${src})
    endforeach()
endmacro()

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

make_execs()
