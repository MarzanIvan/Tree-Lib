cmake_minimum_required(VERSION 3.27)
project(demo)

set(CMAKE_CXX_STANDARD 17)

add_executable(demo main.cxx)

include_directories(treelib)
include_directories(treelib/include)
target_link_libraries(demo /opt/demo/treelib/libTree_Lib.hxx)




