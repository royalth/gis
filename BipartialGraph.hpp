#ifndef BG_HPP
#define BG_HPP

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std; 

const int MAXV = 100000;
const int NIL = 0; 
const int INF = 2000000000;

class BipartialGraph {
	private:
		int V_l, V_r, min_r, max_r, min_l, max_l; 
		
		vector<int> edges[MAXV]; 	// graf: lista sąsiedztwa dla wierzhcołków z lewej strony
									// są to wierzchołki połączone krawędziami
		int matching[MAXV]; 
									
		bool hopcroftKarp(int size);
		bool hopcroftKarpForInterval(int first, int last); 
	public:
		BipartialGraph(); 
		void addEdge(int l, int r);  
		vector< pair<int, int> > findMatchingOfSize(int size); 
};

#endif // BG_HPP