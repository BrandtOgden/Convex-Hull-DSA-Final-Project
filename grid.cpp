#include "grid.h"
#include <cmath>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
//#include <graphviz/gvc.h> // need to use -lgraphviz argument when compiling.
// Note: gvc cgraph has been added to CMakeLists to declare which parts of the library we're using

// Constructor for a Grid
// TODO COULD CHANGE INPUT FROM TEXT FILE TO BE HANDLED HERE
Grid::Grid(std::string f_name, int r, int c) {
//    // Hard coding these values for the time being
//    // TODO WILL NEED TO BE CHANGED IN ACTUAL IMPLEMENTATION
//    this->grid = {{0, 1, 0, 0, 0},
//                  {1, 0, 1, 1, 0},
//                  {0, 0, 1, 0, 1},
//                  {0, 0, 0, 0, 1},
//                  {0, 1, 0, 0, 0}};
//    this->rows = 5;
//    this->cols = 5;
//    // TODO WILL EVENTUALLY CALL get_bottom_point
//    this->bot_left_point = Point(4, 1);
//

//Map vector

    this->rows = r;
    this->cols = c;
    std::vector<std::vector<int> > grid = std::vector<std::vector<int> >(r, std::vector<int>(c, 0));;

    std::ifstream file_ptr;
    file_ptr.open(f_name);
    std::string temp;
    std::string placeholder;
    std::stringstream str_ptr(placeholder);

    //Constructs Map
    for (int row = 0; row < rows; row++) {
        std::getline(file_ptr, placeholder);
        str_ptr.str(placeholder);
        str_ptr.clear();
        str_ptr.seekg(0);

        for (int col = 0; col < cols; col++) {
            str_ptr >> temp;
            //Prints Map
            std::cout<<temp<< " ";

            grid[row][col] = std::stoi(temp);
        }
        std::cout<<"\n";

    }

    //Prints Rows/Cols
    std::cout<<"\n";
    std::cout<<rows<< " ";
    std::cout<<cols<< " ";
}

// Goes through the grid and adds all the points to the vector except for the bottom leftmost point
std::vector<Point> Grid::get_all_points() {

    std::vector<Point> points;

    // Loop through the grid
    for (int row = 0; row < this->grid.size(); row++) {
        for (int col = 0; col < this->grid[row].size(); col++) {
            // If there is a 1, and it's not the bottom leftmost point add the row and col to all_points vector
            if (this->grid[row][col] == 1 && (this->bot_left_point.row != row || this->bot_left_point.col != col)) {
                points.push_back(Point(row, col));
            }
        }
    }

    return points;
}

// Sorts points based on their slopes so there is no need to calculate the angle
void Grid::sort_points() {
    // Gets all the points except for bottom leftmost point and puts them in all_points
    std::vector<Point> points = this->get_all_points();

    // Loop through all the points
    for (int i = 0; i < points.size(); i++) {
        // Calculate their slopes
        points[i].calculate_point_slope(this->bot_left_point);
    }

    // Output all the points and their slopes with the bottom leftmost point
    for (int i = 0; i < points.size(); i++) {
        std::cout << points[i].row << "," << points[i].col << " Slope: "
                  << points[i].slope << std::endl;
    }

    // Vector to hold points with slopes >= 0
    std::vector<Point> positive_slope_points;
    // Vector to hold points with slopes < 0
    std::vector<Point> negative_slope_points;
    // Vector to hold points with undefined slopes or -inf
    std::vector<Point> undefined_slope_points;

    // Puts the points into their respective vector based on their slope
    // unsorted_slopes and all_points are parallel vector
    for (int i = 0; i < points.size(); i++) {
        if (points[i].slope >= 0) {
            positive_slope_points.push_back(points[i]);
        } else if (points[i].slope < 0) {
            negative_slope_points.push_back(points[i]);
        } else {
            undefined_slope_points.push_back(points[i]);
        }
    }

    // TODO THINK ABOUT THIS
    // TODO COULD BE A BETTER WAY TO DO IT?

    // TODO

}

<<<<<<< Updated upstream
// Sorts a vector of points based on their slopes
void Grid::sort(std::vector<Point> vector) {
    
}
=======
    // bottom left to sorted[0] (always true)
    add_edge(ss, std::to_string(bot_left_point.row) + std::to_string(bot_left_point.col),
             std::to_string(this->sorted_points[0].row) + std::to_string(this->sorted_points[0].col), "green");
    render_graph(ss, std::to_string(get_graph_count()) + ".png");

    // sorted[0] go blue
    edit_graph(ss, std::to_string(this->sorted_points[0].row) + std::to_string(this->sorted_points[0].col), "blue");
    render_graph(ss, std::to_string(get_graph_count()) + ".png");

    // bottom left to sorted[0] (always true)
    add_edge(ss, std::to_string(this->sorted_points[0].row) + std::to_string(this->sorted_points[0].col), std::to_string(this->sorted_points[1].row) + std::to_string(this->sorted_points[1].col), "green");
    render_graph(ss, std::to_string(get_graph_count()) + ".png");

    // sorted[1] go blue
    edit_graph(ss, std::to_string(this->sorted_points[1].row) + std::to_string(this->sorted_points[1].col), "blue");
    render_graph(ss, std::to_string(get_graph_count()) + ".png");

    // Loop through until the rest of the points in sorted_points

    std::cout << "now in loop..." << std::endl;
    for (int i = 2; i < this->sorted_points.size(); i ++) {
        // The point that is on the top of the stack is the point that we are unsure if it is actually
        // part of the convex hull
        Point middle_point = convex_hull.top();
        // Remove that point from the stack for now
        convex_hull.pop();
        // If the point at the top of the stack, the middle point, and the point in sorted points turn right
        if (turn_right(convex_hull.top(), middle_point, this->sorted_points[i])) {

            // GRAPHING
            // top to middle (always true)
            add_edge(ss, std::to_string(convex_hull.top().row) + std::to_string(convex_hull.top().col),
                     std::to_string(middle_point.row) + std::to_string(middle_point.col), "red");
            render_graph(ss, std::to_string(get_graph_count()) + ".png");

            // first sorted point go blue
            edit_graph(ss, std::to_string(this->sorted_points[0].row) + std::to_string(this->sorted_points[0].col), "blue");
            render_graph(ss, std::to_string(this->get_graph_count())+".png");

            // middle to sorted[i] (always false)
            add_edge(ss, std::to_string(middle_point.row) + std::to_string(middle_point.col),
                     std::to_string(this->sorted_points[i].row) + std::to_string(this->sorted_points[i].col), "red");
            render_graph(ss, std::to_string(get_graph_count()) + ".png");
>>>>>>> Stashed changes

            // top to middle (always false)
            add_edge(ss, std::to_string(convex_hull.top().row) + std::to_string(convex_hull.top().col),
                     std::to_string(middle_point.row) + std::to_string(middle_point.col), "white");

            // middle to sorted[i] (always false)
            add_edge(ss, std::to_string(middle_point.row) + std::to_string(middle_point.col),
                     std::to_string(this->sorted_points[i].row) + std::to_string(this->sorted_points[i].col), "white");

            // middle point go black
            edit_graph(ss, std::to_string(middle_point.row) + std::to_string(middle_point.col), "black");
            render_graph(ss, std::to_string(get_graph_count())+".png");

            // sorted[i] go blue
            edit_graph(ss, std::to_string(this->sorted_points[i].row) + std::to_string(this->sorted_points[i].col), "blue");
            render_graph(ss, std::to_string(this->get_graph_count())+".png");

<<<<<<< Updated upstream
bool turn_right(Point p1, Point p2, Point p3) {
    Point tempP2 = p2;
    Point tempP3 = p3;

    tempP2.calculate_point_slope(p1);
    tempP3.calculate_point_slope(p1);
//
//
//    float riseP2, riseP3;
//    // Similar code to the calculate_point_slope function
//    if (p1.row == p2.row) {
//        riseP2 = 0;
//    } else {
//        riseP2 = p2.row - p1.row;
//    }
//
//    if (p1.row == p3.row) {
//        riseP3 = 0;
//    } else {
//        riseP3 = p3.row - p1.row;
//    }
//
//    // Calculates the length of the run
//    float runP2, runP3;
//    // If it is in the same column as bot left point
//    if (p1.col == p2.col) {
//        runP2 = 0;
//    } else {
//        runP2 = p1.col - p2.col;
//    }
//
//    if (p1.col == p3.col) {
//        runP3 = 0;
//    } else {
//        runP3 = p1.col - p3.col;
//    }
//
//    // Calculates the slope
//    // If adjacent is 0 then the slope is undefined -inf
//    int slopeP2 = riseP2 / runP2;
//    int slopeP3 = riseP3 / runP3;

    // If P2's slope is positive and P3's slope is negative (automatic false)
    if (tempP2.slope > 0 and tempP3.slope < 0) {
        return false;
    }
=======
            // top to sorted[i] (always true)
            add_edge(ss, std::to_string(convex_hull.top().row) + std::to_string(convex_hull.top().col),
                     std::to_string(sorted_points[i].row) + std::to_string(sorted_points[i].col), "green");
            render_graph(ss, std::to_string(get_graph_count()) + ".png");
>>>>>>> Stashed changes

            // sorted[i] go blue
            edit_graph(ss, std::to_string(this->sorted_points[i].row) + std::to_string(this->sorted_points[i].col), "blue");
            render_graph(ss, std::to_string(this->get_graph_count())+".png");


<<<<<<< Updated upstream
    // If both are positive
    else if (tempP2.slope > 0 and tempP3.slope > 0) {
        //Does not turn right or it is parallel with P1 and P2
        if (tempP2.slope <= tempP3.slope) {
            return false;
        }

        else {
            return true;
        }
    }

=======
            // top to middle (always true)
            add_edge(ss, std::to_string(convex_hull.top().row) + std::to_string(convex_hull.top().col),
                     std::to_string(middle_point.row) + std::to_string(middle_point.col), "green");
            render_graph(ss, std::to_string(get_graph_count()) + ".png");

            // top go blue
            edit_graph(ss, std::to_string(convex_hull.top().row) + std::to_string(convex_hull.top().col), "blue");
            render_graph(ss, std::to_string(get_graph_count())+".png");

            // middle to sorted[i] (always true)
            add_edge(ss, std::to_string(middle_point.row) + std::to_string(middle_point.col), std::to_string(this->sorted_points[i].row) + std::to_string(sorted_points[i].col), "green");
            render_graph(ss, std::to_string(get_graph_count()) + ".png");

            // middle point go blue
            edit_graph(ss, std::to_string(middle_point.row) + std::to_string(middle_point.col), "blue");
            render_graph(ss, std::to_string(get_graph_count())+".png");
        }
    }

    // top to bottom left (always true)
    add_edge(ss, std::to_string(convex_hull.top().row) + std::to_string(convex_hull.top().col),
             std::to_string(bot_left_point.row) + std::to_string(bot_left_point.col), "green");
    render_graph(ss, std::to_string(get_graph_count()) + ".png");

    return convex_hull;
}

void Grid::display_grid() {
    for (int row = 0; row < this->rows; row++) {
        for (int col = 0; col < this->cols; col++) {
            std::cout << grid[row][col] << " ";
        }
        std::cout << "\n";
    }
}

Point Grid::get_bottom_point() {
    return this->bot_left_point;
}

void Grid::set_bottom_point() {
    //this method will loop through the grid to find the lowest most left point
    for (int i = this->rows - 1; i >= 0; i--){
        for (int j = 0; j < this->cols; j++){
            if (this->grid[i][j] == 1) {
                this->bot_left_point = Point(i, j);
                return;
            }
        }
    }
}

bool Grid::turn_right(Point p1, Point p2, Point p3) {
    //Cross product is a measurement of the two points angle in respect to p1
    //Eliminates the need to calculate slope
    float cross_product = ((p2.row - p1.row) * (p3.col - p1.col)) - ((p2.col - p1.col) * (p3.row - p1.row));

    //To determine if p3 is to the right (d -> cross_product):
        //if (d>0) then C is to the left
        //if (d=0) then C is on the same line
        //if (d<0) then C is to the right.

    //Returns true if dots turn right
    if (cross_product < 0) {
        return true;
    }
>>>>>>> Stashed changes
    else {
        return false;
    }

//Find respective slope of P2-P1 and P3-P1
//Slope respective to P1?
}


<<<<<<< Updated upstream
/*
// TODO TEMPORARY DOT PLOT EXAMPLE
void Grid::export_graph() {
    GVC_t *gvc;
    Agraph_t *g;

    // Initialize the Graphviz context
    gvc = gvContext();

    // Create a new graph
    g = agopen("MyGraph", Agdirected, NULL);
=======
    // using dot language from graphviz and the libraries to export the graph
    std::stringstream ss;
    ss << "digraph {\n\tlayout=dot\n\tsplines=false" << std::endl;

    // applies global attributes to points and edges
    ss << "\tnode [shape=point, fixedsize=true, width=0.3, style=filled]\n\tedge [dir=none, penwidth=3]" << std::endl;

    ss << "\tnodesep=4" << std::endl;  // set the horizontal spacing between nodes
    ss << "\tranksep=4" << std::endl;  // set the vertical spacing between ranks
>>>>>>> Stashed changes

    // Add some nodes and edges to the graph
    Agnode_t *node1 = agnode(g, (char*)"Node 1", true);
    Agnode_t *node2 = agnode(g, (char*)"Node 2", true);
    Agnode_t *node3 = agnode(g, (char*)"Node 3", true);
    Agedge_t *edge1 = agedge(g, node1, node2, (char*)"Edge 1", true);
    Agedge_t *edge2 = agedge(g, node2, node3, (char*)"Edge 2", true);

<<<<<<< Updated upstream
    // Generate the DOT output
=======
            // case for the bottom left point
            if (r == this->bot_left_point.row && c == this->bot_left_point.col) {
                //ss << "\t" << std::to_string(r) + std::to_string(c) << " [shape=point,color=black]" << std::endl; TODO TESTING
                ss << "\t" << std::to_string(r) + std::to_string(c) << " [label=\""+std::to_string(r)+","+std::to_string(c)+"\",color=black]" << std::endl;
            }
        }
    }

    // set the color of the points in the vector to black
    for (auto &i: points) {
        //ss << "\t" << std::to_string(i.row) + std::to_string(i.col) << " [shape=point,color=black]" << std::endl; TODO TESTING
        ss << "\t" << std::to_string(i.row) + std::to_string(i.col) << " [label=\""+std::to_string(i.row)+","+std::to_string(i.col)+"\",color=black]" << std::endl;
    }

    // create the main edges hat will link the grid together (default white)
    for (int r = 0; r < this->rows; r++) {
        ss << "\t{rank=same ";
        for (int c = 0; c < this->cols; c++) {
            ss << std::to_string(r) + std::to_string(c) + " ";
        }
        ss << "}\n";
    }

    // create the horizontal edges (default white)
    for (int r = 0; r < this->rows-1; r++) {
        for (int c = 0; c < this->cols; c++) {
            ss << "\t" + std::to_string(r) + std::to_string(c) + " -> " + std::to_string(r+1) + std::to_string(c) + " [style=invis]\n";
        }
    }

    // create the vertical edges (default white)
    for (int r = 0; r < this->rows; r++) {
        for (int c = 0; c < this->cols-1; c++) {
            ss << "\t" + std::to_string(r) + std::to_string(c) + " -> " + std::to_string(r) + std::to_string(c+1) + " [style=invis]\n";
        }
    }
    ss << "}";

    return ss.str();
}

bool Grid::edit_graph(std::string& ss, std::string str, std::string color) {
    std::string search_str;
    std::string replace_str;

    if (str.find("->") != std::string::npos) {
        search_str = str;
        replace_str = "\t" + str + " [color=" + color + "]";
    } else  {
        // the user has entered a point, take the point and create a string to find that ignores the color
        // and a string with the color we want to place
        search_str = str + " [label=\"" + str.substr(0,1) + "," + str.substr(1);
        replace_str = "\t" + str + " [label=\"" + str.substr(0,1) + "," + str.substr(1) + "\",color=" + color + "]";
    }

    // perform the find and replace on the string
    std::stringstream ss_new(ss);
    std::string line;

    bool found = false;

    // iterate over each line in the string and check if the line contains the search_str
    while (std::getline(ss_new, line)) {
        if (line.find(search_str) != std::string::npos) {
            // if so get the starting position of the line and replace the entire line with replace_str
            // this is so there's no need to worry about the previous color
            size_t pos = ss.find(line);

            ss.replace(pos, line.length(), replace_str);
            found = true;
        }
    }

    return found;
}

void Grid::add_edge(std::string& ss, std::string p1, std::string p2, std::string color) {
    // sort points so p1 is smaller and p2 is large for simplicity
    std::string temp;
    if (std::stoi(p1) > std::stoi(p2)) {
        temp = p1;
        p1 = p2;
        p2 = temp;
    }

    std::cout << p1 << ", " << p2 << std::endl;

    // Remove the closing brace and new line from the end of the string
    ss = ss.substr(0, ss.length() - 2);
    ss += "\n";

    // add a new edge to the dot file if it doesn't already exist
    // handles existing horizontal and vertical edges to maintain the grid structure
    if (!edit_graph(ss, p1 + " -> " + p2, color)) {
        ss = ss + "\t" + p1 + " -> " + p2 + " [color=" + color + "]";
    }

    ss += "\n}";
}

void Grid::render_graph(std::string& ss, std::string graph_name) {
    std::cout << graph_name << std::endl;
    std::cout << ss << std::endl;

    // render the graph to a PNG file
    GVC_t *gvc = gvContext();
    Agraph_t *g = agmemread(ss.c_str());
>>>>>>> Stashed changes
    gvLayout(gvc, g, "dot");
    gvRenderFilename(gvc, g, "png", "myplot.png");

    // Free the graph and context resources
    agclose(g);
    gvFreeContext(gvc);

    this->graph_count++;
}
<<<<<<< Updated upstream
*/
=======

int Grid::get_graph_count() const {
    return this->graph_count;
}

void Grid::set_graph_count(int graphCount) {
    this->graph_count = graphCount;
}


>>>>>>> Stashed changes
