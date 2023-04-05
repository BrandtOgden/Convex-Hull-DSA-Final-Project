#include "grid.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <graphviz/gvc.h> // need to use -lgraphviz argument when compiling

int main(int argc, char* argv[]) {

    GVC_t *gvc;
    Agraph_t *g;

    // Initialize the Graphviz context
    gvc = gvContext();

    // Create a new graph
    g = agopen("MyGraph", Agdirected, NULL);

    // Add some nodes and edges to the graph
    Agnode_t *node1 = agnode(g, (char*)"Node 1", true);
    Agnode_t *node2 = agnode(g, (char*)"Node 2", true);
    Agnode_t *node3 = agnode(g, (char*)"Node 3", true);
    Agedge_t *edge1 = agedge(g, node1, node2, (char*)"Edge 1", true);
    Agedge_t *edge2 = agedge(g, node2, node3, (char*)"Edge 2", true);

    // Generate the DOT output
    gvLayout(gvc, g, "dot");
    gvRenderFilename(gvc, g, "png", "myplot.png");

    // Free the graph and context resources
    agclose(g);
    gvFreeContext(gvc);

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
}