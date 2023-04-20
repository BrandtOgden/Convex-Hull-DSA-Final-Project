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

// Grid constructor for random grid
Grid::Grid(int rows, int cols) {
    this->rows = rows;
    this->cols = cols;

    // Use a seed value of the current time to ensure random number generation
    // TODO could potentially have the user input a seed
    std::srand(std::time(nullptr));

    for (int i = 0; i < this->rows; i++) {
        std::vector<int> temp;
        for (int j = 0; j < this->cols; j++) {
            // This gives a 50/50 chance of adding a 0 or a 1
            if (std::rand() % 100 > 50) {
                temp.push_back(1);
            } else {
                temp.push_back(0);
            }
        }
        // Pushes the vector to the class variable
        this->grid.push_back(temp);
    }

    // Get the bottom leftmost point
    set_bottom_point();

}

// Goes through the grid and adds all the points to the vector except for the bottom leftmost point
std::vector<Point> Grid::get_all_points() {

    std::vector<Point> points;

    /*

    // Loop through the points in a circular manner starting at the outside
    // This is so that the points that are furthest to the outside are added first
    // and if they have the same slope with other points inside then they are not added

    int iteration = 0;

    while (iteration != (this->rows / 2) + 1) {
        for (int row = iteration; row < this->rows-iteration; row++) {
            for (int col = iteration; col < this->cols-iteration; col++) {
                if (this->grid[row][col] == 1 && (row == iteration || row == this->rows - iteration - 1)
                && (this->bot_left_point.row != row || this->bot_left_point.col != col)) {
                    points.push_back(Point(row, col));
                } else if (this->grid[row][col] == 1 && (col == iteration || col == this->cols - iteration - 1)
                && (this->bot_left_point.row != row || this->bot_left_point.col != col)) {
                    points.push_back(Point(row, col));
                }
            }
        }
        iteration++;
    }

     */


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
        } else {
            // If a point with the same slope has already been added
            //int index_found = distance(slopes.begin(), pos_found);
            // Add the point that is in the outermost position or has the greatest row
            //if (min_point.row > *pos_found)
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

    // TODO
    // If the size of sorted_points is 1 or there are two total points then a convex hull is not possible

    // The bottom left point is part of the convex hull
    convex_hull.push(this->bot_left_point);
    // The first two points in the sorted array are part of the convex hull
    convex_hull.push(this->sorted_points[0]);
    convex_hull.push(this->sorted_points[1]);

    // bottom left to sorted[0] (always true)
    add_edge(ss, std::to_string(bot_left_point.row) + std::to_string(bot_left_point.col),
             std::to_string(this->sorted_points[0].row) + std::to_string(this->sorted_points[0].col), "green");
    render_graph(ss, std::to_string(get_graph_count()) + ".png");

    // sorted[0] go blue
    edit_graph(ss, std::to_string(this->sorted_points[0].row) + std::to_string(this->sorted_points[0].col), "blue");
    render_graph(ss, std::to_string(get_graph_count()) + ".png");

    // bottom left to sorted[1] (always true)
    add_edge(ss, std::to_string(this->sorted_points[0].row) + std::to_string(this->sorted_points[0].col), std::to_string(this->sorted_points[1].row) + std::to_string(this->sorted_points[1].col), "green");
    render_graph(ss, std::to_string(get_graph_count()) + ".png");

    // sorted[1] go blue
    edit_graph(ss, std::to_string(this->sorted_points[1].row) + std::to_string(this->sorted_points[1].col), "blue");
    render_graph(ss, std::to_string(get_graph_count()) + ".png");

    // Loop through until the rest of the points in sorted_points
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

            // middle to sorted[i] (always false)
            add_edge(ss, std::to_string(middle_point.row) + std::to_string(middle_point.col),
                     std::to_string(this->sorted_points[i].row) + std::to_string(this->sorted_points[i].col), "red");
            render_graph(ss, std::to_string(get_graph_count()) + ".png");

            // reset top to middle
            add_edge(ss, std::to_string(convex_hull.top().row) + std::to_string(convex_hull.top().col),
                     std::to_string(middle_point.row) + std::to_string(middle_point.col), "white");

            // reset middle to sorted[i]
            add_edge(ss, std::to_string(middle_point.row) + std::to_string(middle_point.col),
                     std::to_string(this->sorted_points[i].row) + std::to_string(this->sorted_points[i].col), "white");

            // middle point go black
            edit_graph(ss, std::to_string(middle_point.row) + std::to_string(middle_point.col), "black");
            render_graph(ss, std::to_string(get_graph_count())+".png");

            // Top to sorted[i]
            add_edge(ss, std::to_string(convex_hull.top().row) + std::to_string(convex_hull.top().col),
                     std::to_string(this->sorted_points[i].row) + std::to_string(this->sorted_points[i].col), "green");
            render_graph(ss, std::to_string(get_graph_count()) + ".png");

            // sorted[i] go blue
            edit_graph(ss, std::to_string(this->sorted_points[i].row) + std::to_string(this->sorted_points[i].col), "blue");
            render_graph(ss, std::to_string(this->get_graph_count())+".png");


            // The middle point is not part of the convex hull but the point in sorted points is
            convex_hull.push(this->sorted_points[i]);
        } else {

            // GRAPHING
            // top to middle (always true)
            add_edge(ss, std::to_string(convex_hull.top().row) + std::to_string(convex_hull.top().col),
                     std::to_string(middle_point.row) + std::to_string(middle_point.col), "green");
            render_graph(ss, std::to_string(get_graph_count()) + ".png");

            // top go blue
            edit_graph(ss, std::to_string(convex_hull.top().row) + std::to_string(convex_hull.top().col), "blue");
            render_graph(ss, std::to_string(get_graph_count())+".png");

            // middle to sorted[i] (always true)
            add_edge(ss, std::to_string(middle_point.row) + std::to_string(middle_point.col),
                     std::to_string(this->sorted_points[i].row) + std::to_string(sorted_points[i].col), "green");
            render_graph(ss, std::to_string(get_graph_count()) + ".png");

            // middle point go blue
            edit_graph(ss, std::to_string(middle_point.row) + std::to_string(middle_point.col), "blue");
            render_graph(ss, std::to_string(get_graph_count())+".png");


            // If there is no right turn then the middle point is part of the convex hull
            convex_hull.push(middle_point);
            convex_hull.push(this->sorted_points[i]);
        }
    }

    // top go blue
    edit_graph(ss, std::to_string(convex_hull.top().row) + std::to_string(convex_hull.top().col), "blue");
    render_graph(ss, std::to_string(get_graph_count())+".png");

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
    if (cross_product <= 0) {
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
            // set the color of the point to white by defaultss << "\t" << std::to_string(r) + std::to_string(c)
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
        << " [label=\""+std::to_string(i.row)+","+std::to_string(i.col)+"\",color=black]\n"
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
    gvLayout(gvc, g, "dot");
    gvRenderFilename(gvc, g, "png", (graph_name).c_str());
    // Free the graph and context resources
    agclose(g);
    gvFreeContext(gvc);
    this->graph_count++;
}

int Grid::get_graph_count() {
    return this->graph_count;
}

Point &Grid::get_bottom_point() {
    return bot_left_point;
}
