#include "grid.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {

    std::string f_name = argv[1];
    int row = std::stoi(argv[2]);
    int col = std::stoi(argv[3]);

    Grid g(f_name, row, col);

    g.display_grid();

    // Calculates points in convex hull
    // FOR RIGHT NOW JUST PRINTS THE CASE FOR AN ERROR IN TURN_RIGHT
    std::stack<Point> stack = g.calculate_convex_hull();

    // Displays the stack
    /*
    while (!stack.empty()) {
        std::cout << stack.top().get_row() << "," << stack.top().get_col() << std::endl;
        stack.pop();
    }
     */

    /* TODO

    must download pkg-config-lite and graphviz
    need to note all of this in the report
    make sure to check the box to add environment variable when installing graphviz


    update your CMAkeLists (may need to adjust file paths and things)

    cmake_minimum_required(VERSION 3.24)
    project(Convex_Hull_DSA_Final_Project)

    set(CMAKE_CXX_STANDARD 11)

    set(GRAPHVIZ_INCLUDE_DIRS "C:/Program Files (x86)/Graphviz/include")
    set(GRAPHVIZ_LIBRARY_DIRS "C:/Program Files (x86)/Graphviz/lib")
    include_directories(${GRAPHVIZ_INCLUDE_DIRS})
    link_directories(${GRAPHVIZ_LIBRARY_DIRS})

    add_executable(Convex_Hull_DSA_Final_Project main.cpp grid.cpp grid.h)
    target_link_libraries(Convex_Hull_DSA_Final_Project gvc cgraph)
     */
};