#include <iostream>
#include <vector>

class Grid {
private:
    int rows;
    int cols;
    // Holds the input file
    std::vector<std::vector<int>> grid;
    std::vector<std::pair<int, int>> sorted_points;
    
public:
    std::pair<int , int> find_bot_left();
    void sort_points();
    void calculate_convex_hull();
};


