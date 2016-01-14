#include "Graph.hpp"

Graph::Graph() { } 

Graph::Graph(int _V) : V(_V), maxC(0) { } 

void Graph::colorEdge(int v1, int v2, int c) {
	maxC = max(maxC, c); 
	
	for (vector< pair<int, int> >::iterator it = edges[v1].begin(); it != edges[v1].end(); ++it) {
		if (it->first == v2) 
			it->second = c; 
	}
	for (vector< pair<int, int> >::iterator it = edges[v2].begin(); it != edges[v2].end(); ++it) {
		if (it->first == v1) 
			it->second = c; 
	}
	
}

void Graph::addEdge(int v1, int v2) {
	edges[v1].push_back(make_pair(v2, 0)); 
	edges[v2].push_back(make_pair(v1, 0)); 
}

int Graph::getEdgeColor(int v1, int v2) {
	for (vector< pair<int, int> >::iterator it = edges[v1].begin(); it != edges[v1].end(); ++it) {
		if (it->first == v2) 
			return it->second; 
	}
	
	return -1; 
}

int Graph::getEdgesNum(int v) {
	return edges[v].size();  
}

bool Graph::edgeExists(int v1, int v2) {
	for (vector< pair<int, int> >::iterator it = edges[v1].begin(); it != edges[v1].end(); ++it) {
		if (it->first == v2) 
			return true; 
	}
	return false; 
}

bool Graph::edgeWithColorExists(int v, int c) {
	for (vector< pair<int, int> >::iterator it = edges[v].begin(); it != edges[v].end(); ++it) {
		if (it->second == c) 
			return true;  
	}
	return false; 
}

void Graph::colorFirstEdge() {
	edges[1][0].second = 1; 
}

int Graph::getColorsNum() {
	return maxC; 
}

vector< pair<int, int> > Graph::getEdges(int v) {
	return edges[v]; 
}
