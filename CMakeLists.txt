cmake_minimum_required(VERSION 3.22)
project(postfix_to_expression_tree_project)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(postfix_to_expression_tree_project
        tree_node.cpp
        tree_node.h
        tree.h
        tree.cpp
        tree.cpp
        main.cpp
)
