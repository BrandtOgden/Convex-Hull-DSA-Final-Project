#include "grid.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {

    std::string f_name = argv[1];
    int row = std::stoi(argv[2]);
    int col = std::stoi(argv[3]);

    Grid g(f_name, row, col);
    
};