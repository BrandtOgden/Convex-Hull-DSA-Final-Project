/* TODO - Graphviz notes for report
must download graphviz
make sure to check the box to add environment variable when installing graphviz

update your CMAkeLists (may need to adjust file paths and things). Make sure your CMake is compiled using the template from the project then reload it for you.
main thing is to have your Graphviz install path mapped in the CMakeLists file.

Make sure to include CMakeLists text in report.
Specifically, the classes from the Graphvz libraries have been noted in the CMakeLists file like so: gvc cgraph

We need to use -lgraphviz argument when compiling on the command line. */

#include "grid.h"
#include <cmath>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <graphviz/gvc.h>

// Constructor for a Grid
Grid::Grid(std::string f_name, int r, int c) {
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

    // Call to get_bottom point assigns private variable "bottom_left_point" the proper value
    get_bottom_point();
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

    // Vector to hold points with slopes >= 0
    std::vector<Point> positive_slope_points;
    // Vector to hold points with slopes < 0
    std::vector<Point> negative_slope_points;
    // Vector to hold points with undefined slopes or -inf
    std::vector<Point> undefined_slope_points;

    // Puts the points into their respective vector based on their slope
    for (int i = 0; i < points.size(); i++) {
        if (points[i].slope >= 0) {
            positive_slope_points.push_back(points[i]);
        } else if (points[i].slope == -INFINITY) {
            undefined_slope_points.push_back(points[i]);
        } else {
            negative_slope_points.push_back(points[i]);
        }
    }

    // Loop through all the different vectors and append the points with the smallest slopes first
    // Positive slopes
    while (positive_slope_points.size() > 1) {
        Point min_point = positive_slope_points[0];
        int index = 0;
        for (int i = 1; i < positive_slope_points.size(); i++) {
            if (positive_slope_points[i].slope < min_point.slope) {
                min_point = positive_slope_points[i];
                index = i;
            }
        }
        // Add it to sorted points
        this->sorted_points.push_back(min_point);
        // Remove it from the vector
        positive_slope_points.erase(positive_slope_points.begin() + index);
    }
    // When the vector is size 1 add the last one
    this->sorted_points.push_back(positive_slope_points[0]);

    // Add the undefined points
    // The point at the first index will be the outermost point with an undefined slope so that's the only one we need
    this->sorted_points.push_back(undefined_slope_points[0]);

    // Add the lowest negative slopes
    while (negative_slope_points.size() > 1) {
        Point min_point = negative_slope_points[0];
        int index = 0;
        for (int i = 1; i < negative_slope_points.size(); i++) {
            if (negative_slope_points[i].slope < min_point.slope) {
                min_point = negative_slope_points[i];
                index = i;
            }
        }
        // Add it to sorted points
        this->sorted_points.push_back(min_point);
        // Remove it from the vector
        negative_slope_points.erase(negative_slope_points.begin() + index);
    }
    // When the vector is size 1 add the last one
    this->sorted_points.push_back(negative_slope_points[0]);
}

// Actually calculates which points are part of the convex hull
// Returns them as a vector of points
std::stack<Point> Grid::calculate_convex_hull() {
    // Stack to hold the points that are part of the convex hull
    std::stack<Point> convex_hull;

    // Sort all the points based on the angle they make with the bottom leftmost point
    this->sort_points();

    // TODO
    // If the size of sorted_points is 1 or there are two total points then a convex hull is not possible

    // The bottom left point is part of the convex hull
    convex_hull.push(this->bot_left_point);
    // The first two points in the sorted array are part of the convex hull
    convex_hull.push(this->sorted_points[0]);
    convex_hull.push(this->sorted_points[1]);

    /*
    // Loop through until the rest of the points in sorted_points
    for (int i = 2; i < this->sorted_points.size(); i ++) {
        // The point that is on the top of the stack is the point that we are unsure if it is actually
        // part of the convex hull
        Point middle_point = convex_hull.top();
        // Remove that point from the stack for now
        convex_hull.pop();
        // If the point at the top of the stack, the middle point, and the point in sorted points turn right
        if (turn_right(convex_hull.top(), middle_point, this->sorted_points[i])) {
            // The middle point is not part of the convex hull but the point in sorted points is
            convex_hull.push(this->sorted_points[i]);
        } else {
            // If there is no right turn then the middle point is part of the convex hull
            convex_hull.push(middle_point);
            convex_hull.push(this->sorted_points[i]);
        }
    }
     */
    return convex_hull;
}

void Grid::TEST() {
    // Sort the points
    sort_points();

    // Output all the points and their slopes with the bottom leftmost point
    for (int i = 0; i < this->sorted_points.size(); i++) {
        std::cout << this->sorted_points[i].row << "," << this->sorted_points[i].col << std::endl;
    }
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

void Grid::get_bottom_point() {
    //this method will loop through the grid to find the lowest most left point
    for (int i = this->rows - 1; i >= 0; i--){
        for (int j = 0; j < this->cols; j++){
            if (this->grid[i][j] == 1) {
                this->bot_left_point = Point(i, j);
                return;
            }
        }
    }
}