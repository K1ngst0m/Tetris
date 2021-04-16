cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Libs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})


project(tetris)

include_directories(${CMAKE_SOURCE_DIR}/src/include)
link_directories(${CMAKE_SOURCE_DIR}/libs)

file(GLOB src_files ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB inc_files ${CMAKE_SOURCE_DIR}/src/include/**/*.h)

add_executable(${PROJECT_NAME} ${src_files})

target_link_libraries(${PROJECT_NAME} SDL2 SDL2_ttf SDL2_image IrrKlang)

file(COPY resource DESTINATION ${CMAKE_BINARY_DIR})
