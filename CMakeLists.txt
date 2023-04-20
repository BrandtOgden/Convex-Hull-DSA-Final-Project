cmake_minimum_required(VERSION 3.24)
project(Convex_Hull_DSA_Final_Project)

set(CMAKE_CXX_STANDARD 11)

set(GRAPHVIZ_INCLUDE_DIRS "C:/Program Files/Graphviz/include")
set(GRAPHVIZ_LIBRARY_DIRS "C:/Program Files/Graphviz/lib")
include_directories(${GRAPHVIZ_INCLUDE_DIRS})
link_directories(${GRAPHVIZ_LIBRARY_DIRS})

add_executable(Convex_Hull_DSA_Final_Project main.cpp grid.cpp point.cpp)
target_link_libraries(Convex_Hull_DSA_Final_Project gvc cgraph)