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
                  {0, 1, 1, 0, 1},
                  {1, 0, 0, 0, 0}};
    this->rows = 5;
    this->cols = 5;
}

// Goes through the grid and adds all the points to the vector
void Grid::get_all_points() {
    // HARD CODING THIS VALUE FOR NOW
    this->bot_left_point = std::pair<int, int> (4, 0);

    // Loop through the grid
    for (int row = 0; row < this->grid.size(); row++) {
        for (int col = 0; col < this->grid[row].size(); col++) {
            // If there is a 1 add the row and col to all_points vector
            if (this->grid[row][col] == 1) {
                this->all_points.push_back(std::pair<int, int> (row, col));
            }
        }
    }
}

// Sorts those points based on angle it makes with the bottom leftmost point
void Grid::sort_points() {
    // Gets all the points and puts them into the class variable all_points
    this->get_all_points();

    // Vector that holds the unsorted values of theta
    std::vector<float> unsorted_angles;

    // Loop through all the points
    for (int i = 0; i < this->all_points.size(); i++) {
        // Calculates the length of the opposite side of theta
        float opposite = std::abs(this->bot_left_point.first - this->all_points[i].first) + 1;
        // Calculates the length of the adjacent side of theta
        float adjacent = std::abs(this->bot_left_point.second - this->all_points[i].second) + 1;

        // Calculates the angle that the point makes with the bottom leftmost point (theta)
        float theta = std::tan(opposite/adjacent);

        // Add theta to the vector
        unsorted_angles.push_back(theta);
    }

    // Output all the points and their angles with the bottom leftmost point
    for (int i = 0; i < this->all_points.size(); i++) {
        std::cout << this->all_points[i].first << "," << this->all_points[i].second << " Angle: "
            << unsorted_angles[i] << std::endl;
    }
}


// TODO TEMPORARY
void Grid::TEST() {
    sort_points();
}


