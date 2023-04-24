#include "grid.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
    // delete the jpgs from the last run
    system("for %i in (frames\\*.jpg) do del \"%i\"");

    std::string f_name = argv[1];
    int row = std::stoi(argv[2]);
    int col = std::stoi(argv[3]);

    Grid g = Grid(f_name, row, col);

    // Checks for if the file could be opened
    std::ifstream infile("TestFiles/" + f_name);
    if (!infile.is_open()) {
        std::cout << "Couldn't open file, please try again and make sure file is in the correct directory!" << std::endl;
    } else {
        // Display grid on console
        std::cout << f_name << " Grid:" << std::endl;
        g.display_grid();

        // GRAPHING
        // generate a grid then add the basic polygon to it
        std::string ss = g.base_graph();
        g.render_graph(ss, g.graph_name());

        // highlighted bottom-left point
        std::string bot_left_row = std::to_string(g.get_bottom_point().get_row());
        std::string bot_left_col = std::to_string(g.get_bottom_point().get_col());

        // enter either a point or an edge (point -> point)
        g.edit_graph(ss, bot_left_row + bot_left_col, "blue");
        g.render_graph(ss, g.graph_name());

        std::stack<Point> stack = g.calculate_convex_hull(ss);

        if (!stack.empty()) {
            // create the gif
            std::cout << "\n";
            std::cout << "Please wait while we generate a gif..." << std::endl;
            std::cout << "\n";
            g.generate_gif();
        } else {
            std::cout << "ERROR THIS INPUT COULD NOT CREATE A CONVEX HULL BECAUSE THERE AREN'T ENOUGH POINTS"
                      << std::endl;
        }
    }
}