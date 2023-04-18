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
<<<<<<< Updated upstream
    //std::vector<std::pair<int, int>> sorted_points;
=======
    int graph_count = 1;
public:
    void set_graph_count(int graphCount);

public:
    int get_graph_count() const;

private:
    std::vector<Point> sorted_points;
>>>>>>> Stashed changes

    // Helper methods for calculating the convex hull
    void find_bot_left();
    std::vector<Point> get_all_points();
    void sort_points();
    void sort(std::vector<Point> vector);
    bool turn_right(Point p1, Point p2, Point p3);
    
public:
    // TODO CAN CHANGE SO THAT INPUT FROM TEXT FILE IS BEING DONE IN CONSTRUCTOR
    Grid(std::string fname, int rows, int cols);
    void calculate_convex_hull();

    // TODO TEMPORARY FUNCTION TO TEST GET AND SORT POINTS
    void TEST();

<<<<<<< Updated upstream
    //Grid(std::string f_name, int rowCount, int colCount);

};


=======
    std::string base_graph();
    bool edit_graph(std::string &ss, std::string str, std::string color);
    void add_edge(std::string& ss, std::string p1, std::string p2, std::string color);
    void remove_edge(std::string& ss);
    void render_graph(std::string& ss, std::string graph_name);
};
>>>>>>> Stashed changes
