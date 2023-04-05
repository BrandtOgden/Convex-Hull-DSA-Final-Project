#include "grid.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>



int main(int argc, char* argv[]) {

    std::string f_name = argv[1];
    int row = atoi(argv[2]);
    int col = atoi(argv[3]);

    Grid g(f_name, row, col);

//Need to find why grid, rows, and col are not identified as global

//Map vector
    std::vector<std::vector<int> > grid = std::vector<std::vector<int> >(row, std::vector<int>(col, 0));;

    std::ifstream file_ptr;
    file_ptr.open(f_name);
    std::string temp;
    std::string placeholder;
    std::stringstream str_ptr(placeholder);

//Constructs Map
    for (int r = 0; r < row; r++) {
        std::getline(file_ptr, placeholder);
        str_ptr.str(placeholder);
        str_ptr.clear();
        str_ptr.seekg(0);

        for (int c = 0; c < col; c++) {
            str_ptr >> temp;
            std::cout<<temp<< " ";

            grid[r][c] = std::stoi(temp);
        }
        std::cout<<"\n";

    }
    std::cout<<"\n";
    std::cout<<row<< " ";
    std::cout<<col<< " ";


};