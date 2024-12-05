cmake_minimum_required(VERSION 3.10)
set (CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_COMPILER "g++")
# set(CMAKE_C_COMPILER "gcc")

project(Battleship)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)