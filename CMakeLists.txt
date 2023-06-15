cmake_minimum_required(VERSION 3.24)
project(avl_tree)

set(CMAKE_CXX_STANDARD 20)

add_library(avl_tree INTERFACE)
target_include_directories(avl_tree INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})