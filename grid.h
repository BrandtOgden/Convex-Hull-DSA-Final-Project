#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
#include "point.h"

class Grid {
private:
    int rows;
    int cols;
    Point bot_left_point;

    std::vector<std::vector<int>> grid;
    std::vector<Point> sorted_points;

    int graph_count = 1;

    // Helper methods for calculating the convex hull
    void set_bottom_point();
    std::vector<Point> get_all_points();
    void sort_points();
    bool turn_right(Point p1, Point p2, Point p3);

public:
    Grid();
    Grid(std::string fname, int rows, int cols);
    Grid(int rows, int cols);
    Point &get_bottom_point();

    void display_grid();
    std::stack<Point> calculate_convex_hull(std::string ss);

    // Helper methods for graphing the convex hull
    std::string base_graph();

    bool edit_graph(std::string &ss, std::string str, std::string color);
    void add_edge(std::string &ss, std::string p1, std::string p2, std::string color);
    void render_graph(std::string &ss, std::string graph_name);
    void generate_gif();

    std::string graph_name();
};