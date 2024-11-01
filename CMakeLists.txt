cmake_minimum_required(VERSION 3.11)

project(seven-seg)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")

find_package(SDL2 REQUIRED)

aux_source_directory(. SRC_FILES)

add_executable(seven-seg ${SRC_FILES})

target_link_libraries(seven-seg SDL2)
target_compile_options(seven-seg PRIVATE -fsanitize=address)
