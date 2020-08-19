
#include <stdlib.h>
#include <iostream>
#include <map>
#include <limits>
#include <vector>
#include <fstream>
using namespace std ;

#include "linked.h"


//constructor
LinkedList::LinkedList() {
   m_header = new Node();
   m_factor = 100;
	 m_size = 0;
	 m_useFile = false;
	
}



//destructor
LinkedList::~LinkedList() {
   Node *current, *next ;

   // cout << "LinkedList destructor called\n" ;
   current = m_header ;

   // Run down the linked list and free everyone

   while (current != NULL) {
      next = current->m_next ;
      current->m_next = NULL ;
      delete current ;
      current = next ;
   }
}


//return size of list
unsigned int LinkedList::size(){
	return m_size;
}


//set the name of file to print data 
void LinkedList::setOutput(const char* s){
	m_useFile = true;
	m_file = s;
}
	

//add node to list
void LinkedList::add(int s, int d, int weight){
	
	Node *current = m_header->m_next;
	Node *last = m_header;
	bool hasS = false;
	bool hasD = false;
	
	while(current != NULL){
		if(current->m_num == s){
			current->add(d, weight);
			hasS = true;
		}
		if(current->m_num == d){
			current->add(s, weight);
			hasD = true;
		}
		last = last->m_next;
		current = current->m_next;
	}
	
	if(!hasS){
		Node *source = new Node(s);
		source->add(d, weight);
		last->m_next = source;
		last = last->m_next;
		m_size++;
	}
	if(!hasD){
		Node *dest = new Node(d);
		dest->add(s, weight);
		last->m_next = dest;
		m_size++;
	}
	
}


//print shortest path from source to dest
void LinkedList::route(int source, int dest){
	
	//max integer (weight of infinity)
	int imax = numeric_limits<int>::max();
	
	//stores least weight. format is weight, node
	map<int, int> nodes;
	
	
	//initialize the maps
	Node *current = m_header->m_next;
	while(current != NULL){
		nodes[current->m_num] = imax;
		current = current->m_next;
	}
	
	//no time to travel to source
	nodes[source] = 0;
	
	vector<int> done;
	nodes = routeHelper(source, nodes, done);
	
	vector<int> path;
	int i = dest;
	int total = 0;
	while(i != source){
		path.push_back(i);
		total += (nodes[i] % m_factor);
		i = (nodes[i] / m_factor);
	}
	path.push_back(source);
	
	//set up where to print
	ofstream output;
	if(m_useFile)
		output.open(m_file);
	ostream &out = m_useFile ? output : cout;
	
	out<<"----------------------------------\n";
	out<<source<<"->"<<dest<<endl;
	for(int i = path.size() - 1; i > 0; i--){
		out<<path.at(i)<<"->";
	}
	out<<path.at(0)<<endl;
	out<<"Total distance: "<<(nodes[dest] % m_factor)<<endl;
	out<<"----------------------------------\n";
	output.close();
}


//print route table for source node
void LinkedList::route(int source){
	
	//max integer (weight of infinity)
	int imax = numeric_limits<int>::max();
	
	//stores least weight. format is weight, node
	map<int, int> nodes;
	
	
	//initialize the maps
	Node *current = m_header->m_next;
	while(current != NULL){
		nodes[current->m_num] = imax;
		current = current->m_next;
	}
	
	//no time to travel to source
	nodes[source] = 0;
	
	vector<int> done;
	nodes = routeHelper(source, nodes, done);
	
	//set up where to print
	ofstream output;
	if(m_useFile)
		output.open(m_file, ios::app);
	ostream &out = m_useFile ? output : cout;
	
	out<<"Routing table of node "<<source<<endl<<"Dest   Hop   Dist\n";
	
	typedef map<int, int>::iterator it_type2;
	for(it_type2 iterator = nodes.begin(); iterator != nodes.end(); iterator++){ 
		if(iterator->second == 0)
			continue;
		out<<"  "<<iterator->first<<"     "<<iterator->second / m_factor<<"     "<<iterator->second % m_factor<<endl;
	}		
	out<<endl;
	output.close();
	
	
	
}


//helper function for route(). Implements Dijkstra's algorithm
map<int, int> LinkedList::routeHelper(int source, map<int, int> nodes, vector<int> done){

	int lowest = numeric_limits<int>::max();
	int index = 0;
	bool skipLoop = false;
	Node *current = m_header->m_next;
	
	//get the current node
	while(current->m_num != source){
		current = current->m_next;
	}
	
	//get the weights for all the neighbors
	for(int i = 0; i < current->neighbors.size(); i++){
		//check for inaccessible weights
		for(int j = 0; j < done.size(); j++){
			if(done.at(j) == current->neighbors.at(i))
				skipLoop = true;
		}
		
		if(skipLoop){
			skipLoop = false;
			continue;
		}
		
		//replace weight if appropriate
		if(current->weights.at(i)   + (nodes[source] % m_factor) < (nodes[current->neighbors.at(i)] % m_factor)) {
			nodes[current->neighbors.at(i)] = current->weights.at(i) + (nodes[source] % m_factor) + (source * m_factor);
		}
		//update lowest
		if(current->weights.at(i) < lowest) {
			lowest = current->weights.at(i);
			index = current->neighbors.at(i);
		}
	}
	
	done.push_back(source);
	
	//stop after all nodes have been visited (index will remain 0)
	if(index){	
		//recurse
		return routeHelper(index, nodes, done);
	}
	else 
		return nodes;
}


//print list to console (print the graph)
void LinkedList::print(){
	
	Node *current = m_header->m_next;
	
	while(current != NULL){
		current->print();
		current = current->m_next;
	}
}


