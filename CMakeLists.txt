cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 14) #This works only on cmake version 3.1
set(CMAKE_CXX_STANDARD_REQUIRED on)
add_definitions(-Wall -g3 -std=c++14)

project(WarehouseGeneticAlgorithm)

set(GOOGLE_MOCK Libraries/gtest)
set(SOURCES_DIR src)
set(HEADERS_DIR inc)

include_directories(${HEADERS_DIR})
add_subdirectory(${GOOGLE_MOCK})

add_executable(WarehouseOptimization ${SOURCES_DIR}/main.cpp)

add_custom_command(
                   OUTPUT WarehouseOptimization
                   COMMAND WarehouseOptimization
                   DEPENDS WarehouseOptimization
                  )

add_custom_target(
                  Run ALL
                  DEPENDS WarehouseOptimization
                 )
