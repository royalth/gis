#include "BipartialGraph.hpp" 

vector< pair<int, int> > BipartialGraph::findMatchingOfSize(int size) {
	vector< pair<int, int> > result; 
	
	if (!hopcroftKarp(size))
		return result; 
	
	for (int i = min_l; i <= max_l; ++i) {
		if (!edges[i].empty())
			result.push_back( make_pair(i, matching[i]) ); 
	}
	return result; 
}

bool BipartialGraph::hopcroftKarp(int size) {
	for (int i = min_r; i <= min_r-size; ++i) {
		// TODO jakieś cleanowanie danych? matching co najmniej
		
		if (hopcroftKarpForInterval(i, i+size))
			return true;
	}
	return false; 
}


bool BipartialGraph::hopcroftKarpForInterval(int first, int last) {
	
}


BipartialGraph::BipartialGraph() {
	min_r = INF;
	max_r = 0; 
	min_l = INF;
	max_l = 0; 
}

void BipartialGraph::addEdge(int l, int r) {
	edges[l].push_back(r); 
	min_r = min(min_r, r); 
	max_r = max(max_r, r); 
	min_l = min(min_l, l); 
	max_l = max(max_l, l); 
}

