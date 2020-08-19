The program will take in graph.txt and make a route table for each node, and show the shortest path
from the given source to the given destination.
 
Each node is stored in a linked list. The nodes know which nodes their neighbors are, and the weight
for each neighboring node. 

The program is hardcoded to output to output.txt, but this can be changed in main.cpp to any other file
by changing the variable 'output', or no file (prints to console). 

The graph is printed to the console for convenience. A screenshot is provided. 

A makefile is provided, with the executable name 'route'. To run, compile with 'make', then execute with './route'. 