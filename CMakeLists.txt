project(rand_json)
set(CMAKE_CXX_STANDARD 20)
cmake_minimum_required(VERSION 3.1.3)
set(TARGET_OBJS "json-objs")
set(TARGET_NAME "${PROJECT_NAME}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

file(GLOB_RECURSE SRC_LIST
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp)

add_library(${TARGET_OBJS} STATIC ${SRC_LIST})

add_executable(${TARGET_NAME} src/main.cpp)

target_link_libraries(${TARGET_NAME} ${TARGET_OBJS})