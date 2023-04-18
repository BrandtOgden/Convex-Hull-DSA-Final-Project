#include "point.h"

// Default Constructor which sets values to default values
Point::Point() {
    this->row = 0;
    this->col = 0;
    this->slope = 0;
}

// Constructor with a row and a col
Point::Point(int row, int col) {
    this->row = row;
    this->col = col;
    this->slope = 0;
}

// Calculates the slope of the point with the bottom leftmost point
void Point::calculate_point_slope(Point bot_left_point) {

    // Calculates the length of the rise
    float rise;
    // If it is in the same row as bot left point
    if (bot_left_point.row == this->row) {
        rise = 0;
    } else {
        rise = this->row - bot_left_point.row;
    }

    // Calculates the length of the run
    float run;
    // If it is in the same column as bot left point
    if (bot_left_point.col == this->col) {
        // The side adjacent to theta is 0
        run = 0;
    } else {
        run = bot_left_point.col - this->col;
    }


    // Calculates the slope
    // If adjacent is 0 then the slope is undefined -inf
    this->slope = rise / run;
}

int Point::get_row() {
    return this->row;
}

int Point::get_col() {
    return this->col;
}