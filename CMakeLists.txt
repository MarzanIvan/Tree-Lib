cmake_minimum_required(VERSION 3.27)

project(Tree_Lib)

set(CMAKE_CXX_STANDARD 17)

add_library(Tree_Lib SHARED libTree_Lib.cpp libTree_Lib.hxx
        BalancedBinaryNode.hxx
        BalancedBinaryTree.hxx
        BinarySearchTree.hxx
        BinaryTree.hxx
        BinaryTreeNode.hxx)

include(CTest)
add_subdirectory(external/googletest)
add_subdirectory(Testing)