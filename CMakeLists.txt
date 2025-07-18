# 标题
cmake_minimum_required(VERSION 3.10.0)
project(SKYENGINE VERSION 0.1.0 LANGUAGES C CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 设置编译选项
if (MSVC)
    add_compile_options(/MP)
    # add_compile_options(/W4) # MSVC的警告等级。若使用这个，请忽略cl.exe(编译器)的D9025警告
    add_compile_options(/utf-8)
    # add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    # add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include_directories(src/dep)

# 设置编译输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR})

add_subdirectory(src/core)
add_subdirectory(src/dep/imgui)
add_subdirectory(src/project)
add_subdirectory(src/editor)