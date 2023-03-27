#include <iostream>
#include <vector>

class grid {
private:
    // Holds the input file
    std::vector<std::vector<int>> grid;
    int num_rows;
    int num_cols;
    std::vector<std::pair<int, int>> sorted_points;
    
public:
    std::pair<int , int> find_bot_left();
    void sort_points();
    void calculate_convex_hull();
};


