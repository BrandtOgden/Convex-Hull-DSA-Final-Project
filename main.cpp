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

    Grid g;
    // If the file name is "random" then use the random grid constructor
    if (f_name == "random") {
        g = Grid(row, col);
    } else {
        g = Grid(f_name, row, col);
    }

    // TODO
    // Currently doesn't output all of the points when they are directly above bottom_left_point
    // Don't think we should need all of those points because the line would go through them anyway
    // Only want to add the outermost when the slopes are equal
    g.display_grid();


    // GRAPHING
    // generate a grid then add the basic polygon to it
    std::string ss = g.base_graph();
    g.render_graph(ss, std::to_string(g.get_graph_count()) + ".png");
    std::cout << "rendering to " << g.get_graph_count() << std::endl;
    // highlighted bottom-left point
    std::string bot_left_row = std::to_string(g.get_bottom_point().get_row());
    std::string bot_left_col = std::to_string(g.get_bottom_point().get_col());
    // enter either a point or an edge (point -> point)
    g.edit_graph(ss, bot_left_row + bot_left_col, "blue");
    g.render_graph(ss, std::to_string(g.get_graph_count()) + ".png");
    std::cout << "rendering to " << g.get_graph_count() << std::endl;

    std::stack<Point> stack = g.calculate_convex_hull(ss);

    while (!stack.empty()) {
        std::cout << stack.top().get_row() << "," << stack.top().get_col() << std::endl;
        stack.pop();
    }

    /* TODO GRAPH TESTING
    g.add_edge(ss, bot_left_row + bot_left_col, "34", "green");
    g.render_graph(ss, std::to_string(g.get_graph_count()) + ".png");
    g.edit_graph(ss, "34", "blue"); // coloring the endpoint also blue and this will be our new point
    g.render_graph(ss, std::to_string(g.get_graph_count()) + ".png");
    g.add_edge(ss, "24", "34", "green");
    g.render_graph(ss, std::to_string(g.get_graph_count()) + ".png");
    g.edit_graph(ss, "24", "blue"); // coloring the endpoint also blue and this will be our new point
    g.render_graph(ss, std::to_string(g.get_graph_count()) + ".png");
    g.add_edge(ss, "24", "13", "green");
    g.render_graph(ss, std::to_string(g.get_graph_count()) + ".png");
    g.edit_graph(ss, "13", "blue"); // coloring the endpoint also blue and this will be our new point
    g.render_graph(ss, std::to_string(g.get_graph_count()) + ".png");*/
}