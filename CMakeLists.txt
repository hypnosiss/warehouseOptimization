cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(WarehouseGeneticAlgorithm)
add_executable(WarehouseOptimization main.cpp)
add_custom_command(
                   OUTPUT optimization.lic
                   COMMAND WarehouseOptimization
                   DEPENDS WarehouseOptimization
                  )

add_custom_target(
                  RunAutomatically ALL
                  DEPENDS optimization.lic
                 )
