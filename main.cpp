#include "grid.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
    /*
    std::string f_name = argv[1];
    int rows = atoi(argv[2]);
    int cols = atoi(argv[3]);


//Need to find why grid, rows, and col are not identified as global

//Map vector
    std::vector<std::vector<int> > grid = std::vector<std::vector<int> >(rows, std::vector<int>(cols, 0));;

    std::ifstream file_ptr;
    file_ptr.open(f_name);
    std::string temp;
    std::string placeholder;
    std::stringstream str_ptr(placeholder);

//Constructs Map
    for (int r = 0; r < rows; r++) {
        std::getline(file_ptr, placeholder);
        str_ptr.str(placeholder);
        str_ptr.clear();
        str_ptr.seekg(0);

        for (int c = 0; c < cols; c++) {
            str_ptr >> temp;
            std::cout<<temp<< " ";

            grid[r][c] = std::stoi(temp);
        }
        std::cout<<"\n";

    }
    std::cout<<"\n";
    std::cout<<rows<< " ";
    std::cout<<cols<< " ";

     */

    // Testing sorting points
    Grid grid("test.txt", 5, 5);
    grid.TEST();
}