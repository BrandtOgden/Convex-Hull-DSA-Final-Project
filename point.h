// README
// This is a class that stores the points along with their slopes
// This is so I don't have to use parallel vectors

#include <iostream>
#include <cmath>

class Point {
private:
    int row;
    int col;

    friend class Grid;

public:
    Point();
    Point(int row, int col);
    void calculate_point_slope(Point bot_left_point);
    float slope;

};
