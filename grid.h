#include <iostream>
#include <vector>
#include <cmath>

class Grid {
private:
    int rows;
    int cols;
    // Holds the input file
    std::vector<std::vector<int>> grid;
    std::pair<int, int> bot_left_point;
    std::vector<std::pair<int, int>> all_points;
    std::vector<std::pair<int, int>> sorted_points;

    // Helper methods for calculating the convex hull
    void find_bot_left();
    void get_all_points();
    void sort_points();
    
public:
    // TODO CAN CHANGE SO THAT INPUT FROM TEXT FILE IS BEING DONE IN CONSTRUCTOR
    Grid(std::string fname, int rows, int cols);
    void calculate_convex_hull();

    // TODO TEMPORARY FUNCTION TO TEST GET AND SORT POINTS
    void TEST();
};


