cmake_minimum_required(VERSION 3.29)
project(NewSplayTrees)

set(CMAKE_CXX_STANDARD 20)

# Only list files that are actually standalone compilation units
add_executable(NewSplayTrees
        main.cpp
        SplayTree.h
        AVLTree.h
        BinarySearchTree.h
)