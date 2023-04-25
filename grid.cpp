#include "grid.h"
#include <cmath>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <graphviz/gvc.h>
#include <ctime>
#include <algorithm>
#include <set>
#include <unistd.h>
#include <cstdlib>
#include <iomanip>

// Default Constructor
Grid::Grid() {
    this->rows = 0;
    this->cols = 0;
}

// Constructor for a Grid with an input file specified by the user
Grid::Grid(std::string f_name, int r, int c) {
    this->rows = r;
    this->cols = c;
    this->grid = std::vector<std::vector<int> >(r, std::vector<int>(c, 0));;

    std::ifstream file_ptr;
    std::string path = "TestFiles/" + f_name;
    file_ptr.open(path);
    int temp;
    std::string placeholder;
    std::stringstream str_ptr(placeholder);

    //Constructs Map
    for (int row = 0; row < this->rows; row++) {
        std::getline(file_ptr, placeholder);
        str_ptr.str(placeholder);
        str_ptr.clear();
        str_ptr.seekg(0);

        for (int col = 0; col < this->cols; col++) {
            str_ptr >> temp;

            this->grid[row][col] = temp;
        }
    }

    // Call to get_bottom point assigns private variable "bottom_left_point" the proper value
    set_bottom_point();
}

// Goes through the grid and adds all the points to the vector except for the bottom leftmost point
std::vector<Point> Grid::get_all_points() {

    std::vector<Point> points;
    
    // Loop through the grid starting from the right
    for (int row = 0; row < this->grid.size(); row++) {
        for (int col = this->grid[row].size(); col >= 0; col--) {
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

    // Vector to hold points with slopes >= 0
    std::vector<Point> positive_slope_points;
    // Vector to hold points with slopes < 0
    std::vector<Point> negative_slope_points;
    // Vector to hold points with undefined slopes or -inf
    std::vector<Point> undefined_slope_points;

    // Set that holds all the slopes, so we don't add duplicate slopes
    // Does this using a set to guarantee O(log n) time complexity
    std::set<float> slopes;

    // Puts the points into their respective vector based on their slope
    for (int i = 0; i < points.size(); i++) {
        if (points[i].slope >= 0) {
            positive_slope_points.push_back(points[i]);
        } else if (points[i].slope == -INFINITY) {
            undefined_slope_points.push_back(points[i]);
        } else {
            negative_slope_points.push_back(points[i]);
        }
    }

    // Loop through all the different vectors and append the points with the smallest slopes first
    // Positive slopes
    while (positive_slope_points.size() > 1) {
        Point min_point = positive_slope_points[0];
        int index = 0;
        for (int i = 1; i < positive_slope_points.size(); i++) {
            if (positive_slope_points[i].slope < min_point.slope) {
                min_point = positive_slope_points[i];
                index = i;
            }
        }
        auto pos_found = slopes.find(min_point.slope);
        // If the slope has not already been added
        if (pos_found == slopes.end()) {
            // Add it to the sorted points vector
            this->sorted_points.push_back(min_point);
            // Add its slope to the slopes set
            slopes.insert(min_point.slope);
        }
        // Remove it from the vector
        positive_slope_points.erase(positive_slope_points.begin() + index);
    }
    // When the vector is size 1 add the last one if that slope has not already been added
    if (positive_slope_points.size() == 1 && slopes.find(positive_slope_points[0].slope) == slopes.end()) {
        this->sorted_points.push_back(positive_slope_points[0]);
    }

    // Add the undefined points
    // The point at the first index will be the outermost point with an undefined slope so that's the only one we need
    if (!undefined_slope_points.empty()) {
        this->sorted_points.push_back(undefined_slope_points[0]);
    }

    // Add the lowest negative slopes
    while (negative_slope_points.size() > 1) {
        Point min_point = negative_slope_points[0];
        int index = 0;
        for (int i = 1; i < negative_slope_points.size(); i++) {
            if (negative_slope_points[i].slope < min_point.slope) {
                min_point = negative_slope_points[i];
                index = i;
            }
        }
        // If the slope has not already been added
        if (slopes.find(min_point.slope) == slopes.end()) {
            // Add it to sorted points
            this->sorted_points.push_back(min_point);
            // Add the slope to the slopes set
            slopes.insert(min_point.slope);
        }
        // Remove it from the vector
        negative_slope_points.erase(negative_slope_points.begin() + index);
    }
    // When the vector is size 1 add the last one
    if (negative_slope_points.size() == 1 && slopes.find(negative_slope_points[0].slope) == slopes.end()) {
        this->sorted_points.push_back(negative_slope_points[0]);
    }
}

// Actually calculates which points are part of the convex hull
// Returns them as a vector of points
std::stack<Point> Grid::calculate_convex_hull(std::string ss) {
    // Stack to hold the points that are part of the convex hull
    std::stack<Point> convex_hull;
    // Sort all the points based on the angle they make with the bottom leftmost point
    this->sort_points();

    // Main part of convex hull algorithm
    if (!(this->sorted_points.empty() || this->sorted_points.size() == 1)) {
        // The bottom left point is part of the convex hull
        convex_hull.push(this->bot_left_point);
        // The first two points in the sorted array are part of the convex hull
        convex_hull.push(this->sorted_points[0]);
        convex_hull.push(this->sorted_points[1]);

        // bottom left to sorted[0] (always true)
        add_edge(ss, std::to_string(bot_left_point.row) + std::to_string(bot_left_point.col),
                 std::to_string(this->sorted_points[0].row) + std::to_string(this->sorted_points[0].col), "green");
        render_graph(ss, graph_name());

        // sorted[0] go blue
        edit_graph(ss, std::to_string(this->sorted_points[0].row) + std::to_string(this->sorted_points[0].col), "blue");
        render_graph(ss, graph_name());

        // sorted[0] to sorted[1] (always true)
        add_edge(ss, std::to_string(this->sorted_points[0].row) + std::to_string(this->sorted_points[0].col),
                 std::to_string(this->sorted_points[1].row) + std::to_string(this->sorted_points[1].col), "green");
        render_graph(ss, graph_name());

        // sorted[1] go blue
        edit_graph(ss, std::to_string(this->sorted_points[1].row) + std::to_string(this->sorted_points[1].col), "blue");
        render_graph(ss, graph_name());

        // Loop through until the rest of the points in sorted_points
        for (int i = 2; i < this->sorted_points.size(); i++) {
            // The point that is on the top of the stack is the point that we are unsure if it is actually
            // part of the convex hull
            Point middle_point = convex_hull.top();
            // Remove that point from the stack for now
            convex_hull.pop();
            // If the point at the top of the stack, the middle point, and the point in sorted points turn right

            // shorthand strings for all the points we need to make the graph
            std::string top_point = std::to_string(convex_hull.top().row) + std::to_string(convex_hull.top().col);
            std::string mid_point = std::to_string(middle_point.row) + std::to_string(middle_point.col);
            std::string sorted_point =
                    std::to_string(this->sorted_points[i].row) + std::to_string(this->sorted_points[i].col);

            if (turn_right(convex_hull.top(), middle_point, this->sorted_points[i])) {

                // start drawing edges to create the convex hull
                // top to middle (always false)
                add_edge(ss, top_point, mid_point, "red");
                render_graph(ss, graph_name());
                render_graph(ss, graph_name());

                // middle to sorted[i] (always false)
                add_edge(ss, mid_point, sorted_point, "red");
                render_graph(ss, graph_name());
                render_graph(ss, graph_name());

                // reset top to middle
                add_edge(ss, top_point, mid_point, "white");

                // reset middle to sorted[i]
                add_edge(ss, mid_point, sorted_point, "white");

                // middle point go black
                edit_graph(ss, mid_point, "black");
                render_graph(ss, graph_name());

                // If sorted_points[i] doesn't also make a right turn then add it
                if (i != this->sorted_points.size()-2 && !turn_right(convex_hull.top(), this->sorted_points[i], this->sorted_points[i+1])) {
                    // Top to sorted[i]
                    add_edge(ss, top_point, sorted_point, "green");
                    render_graph(ss, graph_name());

                    // sorted[i] go blue
                    edit_graph(ss, sorted_point, "blue");
                    render_graph(ss, graph_name());
                    convex_hull.push(this->sorted_points[i]);
                } else {
                    // Update graphics to show sorted_points[i] getting removed
                    // It's not really removed we just don't add it, but we still need to show that visually

                    // Strings to clean up graphics calls
                    top_point = std::to_string(convex_hull.top().row) + std::to_string(convex_hull.top().col);
                    std::string sorted_point_i =
                            std::to_string(this->sorted_points[i].row) + std::to_string(this->sorted_points[i].col);
                    std::string sorted_point_i_1 = std::to_string(this->sorted_points[i+1].row) + std::to_string(this->sorted_points[i+1].col);

                    // top to sorted[i] (always false)
                    add_edge(ss, top_point, sorted_point_i, "red");
                    render_graph(ss, graph_name());
                    render_graph(ss, graph_name());

                    // sorted[i] to sorted[i+1] (always false)
                    add_edge(ss, sorted_point_i, sorted_point_i_1, "red");
                    render_graph(ss, graph_name());
                    render_graph(ss, graph_name());

                    // reset top to sorted[i]
                    add_edge(ss, top_point, sorted_point_i, "white");

                    // reset sorted[i] to sorted[i+1]
                    add_edge(ss, sorted_point_i, sorted_point_i_1, "white");

                    // sorted[i] go black
                    edit_graph(ss, sorted_point_i, "black");
                    render_graph(ss, graph_name());
                }
            } else {
                // top to middle (always true)
                add_edge(ss, top_point, mid_point, "green");
                render_graph(ss, graph_name());

                // top go blue
                edit_graph(ss, top_point, "blue");
                render_graph(ss, graph_name());

                // middle point go blue
                edit_graph(ss, mid_point, "blue");
                render_graph(ss, graph_name());

                // middle to sorted[i] (always true)
                add_edge(ss, mid_point, sorted_point, "green");
                render_graph(ss, graph_name());


                // If there is no right turn then the middle point is part of the convex hull
                convex_hull.push(middle_point);
                convex_hull.push(this->sorted_points[i]);
            }
        }

        // top go blue
        edit_graph(ss, std::to_string(convex_hull.top().row) + std::to_string(convex_hull.top().col), "blue");
        render_graph(ss, graph_name());

        // top to bottom left (always true)
        add_edge(ss, std::to_string(convex_hull.top().row) + std::to_string(convex_hull.top().col),
                 std::to_string(bot_left_point.row) + std::to_string(bot_left_point.col), "green");
        render_graph(ss, "last_frame.jpg");
    }
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
    else {
        return false;
    }
}

std::string Grid::base_graph() {
    std::vector<Point> points = get_all_points();
    std::stringstream ss;

    // using dot language from graphviz and the libraries to export the graph
    ss << "digraph {\n\tlayout=dot\n\tsplines=false" << std::endl;

    // applies global attributes to points and edges
    ss << "\tnode [shape=point, fixedsize=true, width=0.3, style=filled]\n\tedge [dir=none, penwidth=3]" << std::endl;
    ss << "\tnodesep=4" << std::endl;  // set the horizontal spacing between nodes
    ss << "\tranksep=4" << std::endl;  // set the vertical spacing between ranks

    // create a grid of all possible nodes based off the range
    for (int r = 0; r < this->rows; r++) {
        for (int c = 0; c < this->cols; c++) {
            // set the color of the point to white by default
            ss << "\t" << std::to_string(r) + std::to_string(c)
            << " [label=\""+std::to_string(r)+","+std::to_string(c)+"\",color=white]\n";

            // case for the bottom left point
            if (r == this->bot_left_point.row && c == this->bot_left_point.col) {
                ss << "\t" << std::to_string(r) + std::to_string(c)
                << " [label=\""+std::to_string(r)+","+std::to_string(c)+"\",color=black]\n";
            }
        }
    }

    // set the color of the points in the vector to black
    for (auto &i: points) {
        ss << "\t" << std::to_string(i.row) + std::to_string(i.col)
        << " [label=\""+std::to_string(i.row)+","+std::to_string(i.col)+"\",color=black]\n";
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
            ss << "\t" + std::to_string(r) + std::to_string(c) +
            " -> " + std::to_string(r+1) + std::to_string(c) + " [style=invis]\n";
        }
    }
    // create the vertical edges (default white)
    for (int r = 0; r < this->rows; r++) {
        for (int c = 0; c < this->cols-1; c++) {
            ss << "\t" + std::to_string(r) + std::to_string(c) +
            " -> " + std::to_string(r) + std::to_string(c+1) + " [style=invis]\n";
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
        replace_str = "\t" + str + " [color=" + color + ",constraint=false]";
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

    // Remove the closing brace and new line from the end of the string
    ss = ss.substr(0, ss.length() - 2) +"\n";

    // add a new edge to the dot file if it doesn't already exist
    // handles existing horizontal and vertical edges to maintain the grid structure
    if (!edit_graph(ss, p1 + " -> " + p2, color)) {
        ss = ss + "\t" + p1 + " -> " + p2 + " [color=" + color + ",constraint=false]";
    }
    ss += "\n}";
}

void Grid::render_graph(std::string& ss, std::string graph_name) {
    // render the graph to a JPG file
    GVC_t *gvc = gvContext();
    Agraph_t *g = agmemread(ss.c_str());
    gvLayout(gvc, g, "dot");
    gvRenderFilename(gvc, g, "jpg", ("frames/" + graph_name).c_str());
    // Free the graph and context resources
    agclose(g);
    gvFreeContext(gvc);
    this->graph_count++;
}

std::string Grid::graph_name() {
    // takes the current count of the graph to name the file to
    // makes an output file stream to be computable with setfill
    // adds leading 0 to numbers 1-9, so it orders to graph files correctly
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << std::to_string(this->graph_count);
    std::string str = oss.str() + ".jpg";
    return str;
}

Point &Grid::get_bottom_point() {
    return bot_left_point;
}

void Grid::generate_gif() {
    // execute a system command to use the Image Magic API to convert the frames to a gif with 40 milliseconds
    // in between and a delay for 300 milliseconds for the last frame
    system("convert -delay 40 -dispose previous -loop 0 frames/*.jpg -delay 200 frames/last_frame.jpg frames/graph.gif");
    // execute a system command to open the graph for easy access

    std::cout << "Done" << std::endl;

    system("start frames/graph.gif");
}