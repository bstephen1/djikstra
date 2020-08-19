#ifndef _NODE_H_
#define _NODE_H_

#include <vector>

class Node {

  public:

		Node();
		Node(int num);
		void add(int node, int weight);
		void print();
	
	
	//private:
	
		int m_num;
		bool m_done;
		vector<int> neighbors;
		vector<int> weights;
		Node *m_next;
 
};

#endif
