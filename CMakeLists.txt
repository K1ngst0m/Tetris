#CMake最低版本号要求
cmake_minimum_required(VERSION 3.7.1)

#项目信息
project(Tetris)

find_package(LLVM REQUIRED CONFIG)

set(SOURCE_FILES ./include/*.cpp)

aux_source_directory(DIR_SRCS)

add_executable(Tetris${DIR_SRCS})
