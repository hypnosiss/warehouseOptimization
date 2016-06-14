cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 14) #This works only on cmake version 3.1
set(CMAKE_CXX_STANDARD_REQUIRED on)
add_definitions(-Wall -g3 -std=c++14)

project(WarehouseGeneticAlgorithm)

set(SOURCES_DIR src)
set(HEADERS_DIR inc)

include_directories(${HEADERS_DIR})

add_subdirectory(${SOURCES_DIR})

add_executable(WarehouseOptimization ${SOURCES_DIR}/main.cpp
              )

target_link_libraries(WarehouseOptimization Algorithm)

add_custom_command(
                   OUTPUT WarehouseOptimizationRun
                   COMMAND WarehouseOptimization
                   DEPENDS WarehouseOptimization
                  )

add_custom_target(
                  Run ALL
                  DEPENDS WarehouseOptimizationRun
                 )
