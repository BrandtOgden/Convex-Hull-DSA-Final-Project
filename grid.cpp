#include "grid.h"
#include <cmath>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>

// Constructor for a Grid
// TODO COULD CHANGE INPUT FROM TEXT FILE TO BE HANDLED HERE
Grid::Grid(std::string fname, int rows, int cols) {
    // Hard coding these values for the time being
    // TODO WILL NEED TO BE CHANGED IN ACTUAL IMPLEMENTATION
    this->grid = {{0, 1, 0, 0, 0},
                  {1, 0, 1, 1, 0},
                  {0, 0, 1, 0, 1},
                  {0, 0, 0, 0, 1},
                  {0, 1, 0, 0, 0}};
    this->rows = 5;
    this->cols = 5;
    // TODO WILL EVENTUALLY CALL get_bottom_point
    this->bot_left_point = Point(4, 1);
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

    // Output all the points and their slopes with the bottom leftmost point
    for (int i = 0; i < points.size(); i++) {
        std::cout << points[i].row << "," << points[i].col << " Slope: "
                  << points[i].slope << std::endl;
    }

    // Vector to hold points with slopes >= 0
    std::vector<Point> positive_slope_points;
    // Vector to hold points with slopes < 0
    std::vector<Point> negative_slope_points;
    // Vector to hold points with undefined slopes or -inf
    std::vector<Point> undefined_slope_points;

    // Puts the points into their respective vector based on their slope
    // unsorted_slopes and all_points are parallel vector
    for (int i = 0; i < points.size(); i++) {
        if (points[i].slope >= 0) {
            positive_slope_points.push_back(points[i]);
        } else if (points[i].slope < 0) {
            negative_slope_points.push_back(points[i]);
        } else {
            undefined_slope_points.push_back(points[i]);
        }
    }

    // TODO THINK ABOUT THIS
    // TODO COULD BE A BETTER WAY TO DO IT?

    // TODO

}

// Sorts a vector of points based on their slopes
void Grid::sort(std::vector<Point> vector) {
    
}


//Grid::Grid(std::string f_name, int rowCount, int colCount) {
//    // Generate a board from the give file
//    this->rows = rowCount;
//    this->cols = colCount;
//
//
//    //Map vector
//    grid = std::vector<std::vector<int> >(rows, std::vector<int>(cols, 0));;
//
//    std::ifstream file_ptr;
//    file_ptr.open(f_name);
//    std::string temp;
//    std::string placeholder;
//    std::stringstream str_ptr(placeholder);
//
//
//    //Constructs Map
//    for (int r = 0; r < rows; r++) {
//        std::getline(file_ptr, placeholder);
//        str_ptr.str(placeholder);
//        str_ptr.clear();
//        str_ptr.seekg(0);
//
//        for (int c = 0; c < cols; c++) {
//            str_ptr >> temp;
//            std::cout<<temp<< " ";
//
//           grid[r][c] = std::stoi(temp);
//        }
//        std::cout<<"\n";
//    }
//
//
//    std::cout<<"\n";
//    std::cout<<rows<< " ";
//    std::cout<<cols<< " ";
//}

