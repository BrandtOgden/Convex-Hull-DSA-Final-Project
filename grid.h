#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "point.h"

class Grid {
private:
    int rows;
    int cols;
    std::vector<std::vector<int>> grid;
    Point bot_left_point;
    //std::vector<std::pair<int, int>> sorted_points;

    // Helper methods for calculating the convex hull
    std::vector<Point> get_all_points();
    void sort_points();
    bool turn_right(Point p1, Point p2, Point p3);

public:
    // TODO CAN CHANGE SO THAT INPUT FROM TEXT FILE IS BEING DONE IN CONSTRUCTOR
    Grid(std::string fname, int rows, int cols);
    void display_grid();
    void calculate_convex_hull();

    void export_graph();

    void get_bottom_point();
};