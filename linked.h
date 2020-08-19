#ifndef _LINKED_H_
#define _LINKED_H_

#include "node.h"
#include <map>
#include <vector>
#include <iostream>

class LinkedList {

	public:
    LinkedList();
    ~LinkedList();
    void add(int, int, int);
		void print();
		void route(int);
		void route(int, int);
		unsigned int size();
		void setOutput(const char*);

	private:
		map<int, int> routeHelper(int source, map<int, int>, vector<int>);
		unsigned int m_factor, m_size;
		bool m_useFile;
		const char* m_file;
    Node *m_header;
		
};


#endif
