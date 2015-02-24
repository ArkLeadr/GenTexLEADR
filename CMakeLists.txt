project(GenTexLEADR)
cmake_minimum_required(VERSION 2.8)

file(GLOB SRC_LIST "*.cpp")
#file(GLOB SRC_LIST "*.h")

message("Src list : ${SRC_LIST}")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules/")


add_executable(${PROJECT_NAME} ${SRC_LIST})

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g") # features

find_package(DevIL REQUIRED) # DevIL

include_directories(. ${DEVIL_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} ${DEVIL_LIBRARY})
