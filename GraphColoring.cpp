#include "GraphColoring.hpp"

void GraphColoring::findColoring() {
	if (canExclude()) {
		coloringFound = false; 
		return; 
	}
	coloringFound = heuristic();
}

bool GraphColoring::canExclude() {
	if (V % 2 == 0) 
		return false; 
	if (E == V*(V-1)/2)		// graf pełny
		return true; 
	if (E == V)	{
		for (int i = 1; i <= V; ++i) {
			if (g.getEdgesNum(i) != 2)
				return false; 
		}
		return true; 
	}
	return false; 
}

bool GraphColoring::heuristic() {
	for (int v = 1; v <= V; ++v) {
		if (!processVertex(v)) {
			return false; 
		} 
	}
	
	return true; 
}

bool GraphColoring::processVertex(int v) {
	if (!limitInterval(v)) 
		return false; 
	
	BipartialGraph bg; 
	
	for (int v2 = 1; v2 <= V; ++v2) {
		if (!g.edgeExists(v, v2)) 
			continue; 
		if (!processEdge(v, v2, &bg))
			return false; 
	}
	
	return chooseColoringForVertex(v, &bg);
}

bool GraphColoring::processEdge(int v1, int v2, BipartialGraph *bg) { 
	if (!limitInterval(v2))
		return false; 
		
	vector<int> possibleColors = getPossibleColors(v1, v2);
	if (possibleColors.empty())
		return false; 
		
	for (vector<int>::iterator it = possibleColors.begin(); it != possibleColors.end(); ++it) {
		bg->addEdge(v2, *it); 
	}
	
	return true; 
}

bool GraphColoring::limitInterval(int v) {
	int d = g.getEdgesNum(v); 
	for (int v2 = 1; v2 <= V; ++v2) {
		int c = g.getEdgeColor(v, v2); 
		if (c <= 0) 
			continue; 
		
		interval[v].start = max(interval[v].start, c - d + 1); 	// TODO zweryfikuj
		interval[v].end = min(interval[v].end, c + d - 1); 
	}
	
	if (interval[v].start > interval[v].end)		// TODO zweryfikuj
		return false; 
	return true; 
}

vector<int> GraphColoring::getPossibleColors(int v1, int v2) {
	vector<int> colors; 
	for (int c = max(interval[v1].start, interval[v2].start); c <= min(interval[v1].end, interval[v2].end); ++c) {
		if (!g.edgeWithColorExists(v1, c) && !g.edgeWithColorExists(v2, c))
			colors.push_back(c); 
	}
	return colors; 
}

bool GraphColoring::chooseColoringForVertex(int v, BipartialGraph *bg) {
	vector< pair<int, int> > coloring = bg->findMatchingOfSize( g.getEdgesNum(v) ); 
	if (coloring.empty())
		return false; 
	
	for (vector< pair<int, int> >::iterator it = coloring.begin(); it != coloring.end(); ++it) {
		g.colorEdge(v, it->first, it->second); 
	}
	return true; 
}


void GraphColoring::input() {
	cin >> V >> E; 
	
	g = Graph(V); 
	
	int v1, v2; 
	for (int i = 0; i < E; ++i) {
		cin >> v1 >> v2; 
		g.addEdge(v1, v2); 
	}
}

void GraphColoring::output() {
	if (coloringFound) {

		cout << N << endl; 
		for (int v1 = 1; v1 <= V; ++v1) {
			for (int v2 = v1+1; v2 <= V; ++v2) {
				if (g.edgeExists(v1, v2)) {
					cout << v1 << " " << v2 << " " << g.getEdgeColor(v1, v2) << endl; 
				}
			}
		}

	} else {
		cout << "NIE ZNALEZIONO POKOLOROWANIA ZWARTEGO KRAWEDZI TEGO GRAFU" << endl; 
	}
}

GraphColoring::GraphColoring() {
	coloringFound = false; 
}
