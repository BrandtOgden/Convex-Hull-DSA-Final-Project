# Convex-Hull-DSA-Final-Project
**Ryan Brooks, Ryan Shilling, Sam Gryska, Brandt Ogden**

## Summary
Outline of what a convex hull is and Graham's Scan Algorithm  
Outline of our program and how we went about solving the problem

## Planning 
Not sure if we need this   
Talk about on Tuesday

## Compilation Instructions
You can compile the program using this command:
``

``

The output will be a series of images which make up the graph through each step as well as a Gif that can be independently created with the included batch file. 
Since we're using the Dot Language provided by Graphviz, you will need to install Graphviz on your computer to run the program. 

If you're using CLion to compile the program, make sure you:
1. Install Graphviz on your computer https://graphviz.org/download/ Make sure when installing to check the box "Add Graphviz to the system PATH", as seen in the picture below.
   ![graphvizinstallpicture.jpg](graphvizinstallpicture.png)
2. It's recommended you restart your computer
3. If you're compiling on the command line then use this command below. If you're using CLion, please proceed with steps 4 and 5.
```
g++ -o dsa main.cpp grid.cpp point.cpp -IC:/Program Files/Graphviz/include -LC:/Program Files/Graphviz/lib -lgvc -lcgraph
```

4. Make sure this text is included in your CMakeLists.txt in order to properly include your installation directory and to reference which libraries we'll be using.

```
cmake_minimum_required(VERSION 3.24)
project(Convex_Hull_DSA_Final_Project)

set(CMAKE_CXX_STANDARD 11)

set(GRAPHVIZ_INCLUDE_DIRS "C:/Program Files/Graphviz/include")
set(GRAPHVIZ_LIBRARY_DIRS "C:/Program Files/Graphviz/lib")
include_directories(${GRAPHVIZ_INCLUDE_DIRS})
link_directories(${GRAPHVIZ_LIBRARY_DIRS})

add_executable(Convex_Hull_DSA_Final_Project main.cpp grid.cpp point.cpp)
target_link_libraries(Convex_Hull_DSA_Final_Project gvc cgraph)
```
Note that in the "set(GRAPHVIZ_INCLUDE_DIRS..." lines you will need to change the installation directtory to the one you picked when installing Graphviz. The CMakeLists file provided should have the default location.
5. Reload the CMake project






Format for text files  
Option for a random grid?  

## Runtime Instructions
Not sure if we will need any runtime instructions

## Sample Runs
Should probably include this but not sure if it is necessary

