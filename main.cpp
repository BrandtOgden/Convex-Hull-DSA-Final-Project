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

    Grid g;
    // If the file name is "random" then use the random grid constructor
    if (f_name == "random") {
        g = Grid(row, col);
    } else {
        g = Grid(f_name, row, col);
    }

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
        g.generate_gif();
    } else {
        std::cout << "ERROR THIS INPUT COULD NOT CREATE A CONVEX HULL BECAUSE THERE AREN'T ENOUGH POINTS" << std::endl;
    }

    // Outputs the points to the terminal
    while (!stack.empty()) {
        std::cout << stack.top().get_row() << "," << stack.top().get_col() << std::endl;
        stack.pop();
    }

}