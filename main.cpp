#include <iostream>
using namespace std ;

#include "node.h"
#include "linked.h"
#include <fstream>
#include <cstdlib>
#include <vector>

int main() {
	
	LinkedList l = LinkedList();
	int source, dest;
	bool src = true;
	ifstream graph ("graph.txt");
	string s;
	while(graph>>s){
		
		//check if first digit is a number
		if(s[0] > 57 || s[0] < 48){
			int temp = 0;
			for(int i = 0; i <= s.size(); i++){
				if(s[i] <= 57 && s[i] >= 48)
					temp = temp * 10 + (int)s[i] - 48;
			}
			if(src){
				source = temp;
				src = false;
			}
			else 
				dest = temp;
		}
		else{
			vector<int> node;
			int temp = 0;
			for(int i = 0; i <= s.size(); i++){
				if(i == s.size() || s[i] == '$'){
					node.push_back(temp);
					temp = 0;
				}
				else {
					//account for multiple digits
					temp = temp * 10 + (int)s[i] - 48;
				}
			}
			l.add(node.at(0), node.at(1), node.at(2));
		}
	}
	graph.close();
	
	//print the graph to console
	cout<<endl;
	l.print();
	cout<<endl;
	
	//set the output
	const char* output = "output.txt";
	
	l.setOutput(output);
	
	l.route(source,dest);
	
	//route table for each node
	for(int i = 1; i <= l.size(); i++){
		l.route(i);
	}
	
	cout<<"Output is in \""<<output<<"\""<<endl;
	
}