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

#include "grid.h"
#include <cmath>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <graphviz/gvc.h> // need to use -lgraphviz argument when compiling.
// Note: gvc cgraph has been added to CMakeLists to declare which parts of the library we're using

// Constructor for a Grid
Grid::Grid(std::string f_name, int r, int c) {
    // TODO WILL EVENTUALLY CALL get_bottom_point
    this->bot_left_point = Point(4, 1);


    this->rows = r;
    this->cols = c;
    this->grid = std::vector<std::vector<int> >(r, std::vector<int>(c, 0));;

    std::ifstream file_ptr;
    file_ptr.open(f_name);
    int temp;
    std::string placeholder;
    std::stringstream str_ptr(placeholder);

    //Constructs Map
    for (int row = 0; row < this->rows; row++) {
        std::getline(file_ptr, placeholder);
        str_ptr.str(placeholder);
        str_ptr.clear();
        str_ptr.seekg(0);

        for (int col = 0; col < this->cols; col++) {
            str_ptr >> temp;

            this->grid[row][col] = temp;
        }

    }
}

// Goes through the grid and adds all the points to the vector except for the bottom leftmost point
std::vector<Point> Grid::get_all_points() {

    std::vector<Point> points;

    // Loop through the grid
    for (int row = 0; row < this->grid.size(); row++) {
        for (int col = 0; col < this->grid[row].size(); col++) {
            // If there is a 1, and it's not the bottom leftmost point add the row and col to all_points vector
            if (this->grid[row][col] == 1 && (this->bot_left_point.row != row || this->bot_left_point.col != col)) {
                points.push_back(Point(row, col));
            }
        }
    }

    return points;
}

// Sorts points based on their slopes so there is no need to calculate the angle
void Grid::sort_points() {
    // Gets all the points except for bottom leftmost point and puts them in all_points
    std::vector<Point> points = this->get_all_points();

    // Loop through all the points
    for (int i = 0; i < points.size(); i++) {
        // Calculate their slopes
        points[i].calculate_point_slope(this->bot_left_point);
    }

    // Output all the points and their slopes with the bottom leftmost point
    for (int i = 0; i < points.size(); i++) {
        std::cout << points[i].row << "," << points[i].col << " Slope: "
                  << points[i].slope << std::endl;
    }

    // Vector to hold points with slopes >= 0
    std::vector<Point> positive_slope_points;
    // Vector to hold points with slopes < 0
    std::vector<Point> negative_slope_points;
    // Vector to hold points with undefined slopes or -inf
    std::vector<Point> undefined_slope_points;

    // Puts the points into their respective vector based on their slope
    // unsorted_slopes and all_points are parallel vector
    for (int i = 0; i < points.size(); i++) {
        if (points[i].slope >= 0) {
            positive_slope_points.push_back(points[i]);
        } else if (points[i].slope < 0) {
            negative_slope_points.push_back(points[i]);
        } else {
            undefined_slope_points.push_back(points[i]);
        }
    }

    // TODO THINK ABOUT THIS
    // TODO COULD BE A BETTER WAY TO DO IT?

    // TODO

}

// Sorts a vector of points based on their slopes
void Grid::sort(std::vector<Point> vector) {

}

void Grid::export_graph() {
    GVC_t *gvc;
    Agraph_t *g;

    // Initialize the Graphviz context
    gvc = gvContext();

    // Create a new graph
    g = agopen("MyGraph", Agdirected, NULL);

    // Add some nodes and edges to the graph
    Agnode_t *node1 = agnode(g, (char*)"Node 1", true);
    Agnode_t *node2 = agnode(g, (char*)"Node 2", true);
    Agnode_t *node3 = agnode(g, (char*)"Node 3", true);
    Agedge_t *edge1 = agedge(g, node1, node2, (char*)"Edge 1", true);
    Agedge_t *edge2 = agedge(g, node2, node3, (char*)"Edge 2", true);

    // Generate the DOT output
    gvLayout(gvc, g, "dot");
    gvRenderFilename(gvc, g, "png", "myplot.png");

    // Free the graph and context resources
    agclose(g);
    gvFreeContext(gvc);
}

void Grid::display_grid() {
    for (int row = 0; row < this->rows; row++) {
        for (int col = 0; col < this->cols; col++) {
            std::cout << grid[row][col] << " ";
        }
        std::cout << "\n";
    }
}