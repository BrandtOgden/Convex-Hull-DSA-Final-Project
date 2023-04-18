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


<<<<<<< Updated upstream
=======

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

    // Calculates points in convex hull
    // FOR RIGHT NOW JUST PRINTS THE CASE FOR AN ERROR IN TURN_RIGHT
    std::stack<Point> stack = g.calculate_convex_hull(ss);

    // Displays the stack
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
>>>>>>> Stashed changes
};