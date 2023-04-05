#include "grid.h"
#include <cmath>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <graphviz/gvc.h> // need to use -lgraphviz argument when compiling

/* TODO

must download pkg-config-lite and graphviz
need to note all of this in the report
make sure to check the box to add environment variable when installing graphviz


update your CMAkeLists (may need to adjust file paths and things)

cmake_minimum_required(VERSION 3.24)
project(Convex_Hull_DSA_Final_Project)

set(CMAKE_CXX_STANDARD 11)

set(GRAPHVIZ_INCLUDE_DIRS "C:/Program Files (x86)/Graphviz/include")
set(GRAPHVIZ_LIBRARY_DIRS "C:/Program Files (x86)/Graphviz/lib")
include_directories(${GRAPHVIZ_INCLUDE_DIRS})
link_directories(${GRAPHVIZ_LIBRARY_DIRS})

add_executable(Convex_Hull_DSA_Final_Project main.cpp grid.cpp grid.h)
target_link_libraries(Convex_Hull_DSA_Final_Project gvc cgraph)
 */

// TODO TEMPORARY DOT PLOT EXAMPLE
void Grid::export_graph() {
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
}

