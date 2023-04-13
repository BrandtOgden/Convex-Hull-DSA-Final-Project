#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
#include "point.h"

class Grid {
private:
    int rows;
    int cols;
    std::vector<std::vector<int>> grid;
    Point bot_left_point;
    std::vector<Point> sorted_points;

    // Helper methods for calculating the convex hull
    void get_bottom_point();
    std::vector<Point> get_all_points();
    void sort_points();
    bool turn_right(Point p1, Point p2, Point p3);

public:
    Grid(std::string fname, int rows, int cols);
    void display_grid();
    std::stack<Point> calculate_convex_hull();

    void export_graph();
};