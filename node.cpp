#include <iostream>

using namespace std;

#include "node.h"
#include <vector>


Node::Node(){
	
	m_num = NULL;
	m_next = NULL;
}

Node::Node(int num){
	
	m_num = num;
	m_next = NULL;
}


//adds the neighbor with weight if it is not already a neighbor
void Node::add(int node, int weight){
	
	for(int i = 0; i < neighbors.size(); i++){
		if(neighbors.at(i) == node) 
			return;
	}
	
	neighbors.push_back(node);
	weights.push_back(weight);
}


//print neighbors and their weights
void Node::print(){
	
	cout<<"Node "<<m_num<<": ";
	for(int i = 0; i < neighbors.size(); i++){
		cout<<neighbors.at(i)<<"$"<<weights.at(i)<<" ";
	}
	cout<<endl;
}