#include "GraphColoring.hpp"

void GraphColoring::findColoring() {
	if (canExclude()) {
		coloringFound = false; 
		return; 
	}
	coloringFound = heuristic();
}

bool GraphColoring::canExclude() {
	if (V % 2 == 1 && E == V*(V-1)/2)		// graf pełny o nieparzystej liczbie wierzchołków
		return true; 
	if (V % 2 == 0 && E == V-1)	{ 			// cykl o parzystej liczbie wierzchołków (nieparzystej liczbie krawędzi)
		for (int i = 1; i <= V; ++i) {
			if (g.getEdgesNum(i) != 2)
				return false; 
		}
		return true; 
	}
	return false; 
}

bool GraphColoring::heuristic() { 
	g.colorFirstEdge(); 
		
	// przeglądamy w kolejności bfs - dzięki temu zawsze bedziemy przetwarzać wierzchołek, który ma pokolorowaną przynjamniej jedną krawędź
	// ponieważ na kolejkę bedą trafiać sąsiedzi tylko przetworzonych wierzchołków
	queue<int> q; 
	bool visited[V+1]; 
	for (int i = 1; i <= V; ++i)
		visited[i] = false; 
	
	q.push(1); 
	while (!q.empty()) {
		int v = q.front(); 
		q.pop(); 
		visited[v] = true; 
		if (!processVertex(v))
			return false; 
		
		vector< pair<int, int> > edges = g.getEdges(v); 
		for (vector< pair<int, int> >::iterator it = edges.begin(); it != edges.end(); ++it) {
			if (!visited[it->first])
				q.push(it->first); 
		}
	}
	
	return true; 
}


bool GraphColoring::processVertex(int v) {
//	cout << endl << "processVertex v: " << v << endl; 
	
	if (!limitInterval(v)) {
	//	cout << "limit interval v: " << v << endl; 
		return false; 
	}
	
	BipartialGraph bg; 
	
	for (int v2 = 1; v2 <= V; ++v2) {
		if (!g.edgeExists(v, v2)) 
			continue; 
		if (!processEdge(v, v2, &bg)) {
			return false; 
		}
	}
	
	return chooseColoringForVertex(v, &bg);
}

bool GraphColoring::processEdge(int v1, int v2, BipartialGraph *bg) { 
	int c = g.getEdgeColor(v1, v2); 
	if (c > 0) {
		bg->addEdge(v2, c);
		return true; 
	}
	
	if (!limitInterval(v2))  {
		//cout << "limit interval w process edge, v1: " << v1 << ", v2: " << v2 << endl; 
		return false; 
	}
		
	vector<int> possibleColors = getPossibleColors(v1, v2);
	
	if (possibleColors.empty()) { 
		//cout << "possibleColors empty" << endl; 
		return false; 
	}
		
	for (vector<int>::iterator it = possibleColors.begin(); it != possibleColors.end(); ++it) {
		bg->addEdge(v2, *it); 
	}
	
	return true; 
}

bool GraphColoring::limitInterval(int v) {
	int d = g.getEdgesNum(v); 
	for (int v2 = 1; v2 <= V; ++v2) {
		int c = g.getEdgeColor(v, v2); 
		if (c <= 0) 	// krawędź ma juz przypisany kolor
			continue; 
		
		interval[v].start = max(interval[v].start, c - d + 1); 	
		interval[v].end = min(interval[v].end, c + d - 1); 
	}
	
	if (interval[v].start > interval[v].end)	{ 	
		//cout << "v: " << v << ", d: " << d << ", int start: " << interval[v].start << ", int end: " << interval[v].end << endl; 
		return false; 
	}
	return true; 
}

vector<int> GraphColoring::getPossibleColors(int v1, int v2) {
	vector<int> colors; 
	//cout << "max: " << max(interval[v1].start, interval[v2].start) << ", min: " << min(interval[v1].end, interval[v2].end) << endl; 
	//cout << "v1: " << v1 << ", interval start: " << interval[v1].start << ", end: " << interval[v1].end << endl; 
	//cout << "v2: " << v2 << ", interval start: " << interval[v2].start << ", end: " << interval[v2].end << endl; 
	
	for (int c = max(interval[v1].start, interval[v2].start); c <= min(interval[v1].end, interval[v2].end); ++c) {
		if (!g.edgeWithColorExists(v1, c) && !g.edgeWithColorExists(v2, c))
			colors.push_back(c); 
	}
	return colors; 
}

bool GraphColoring::chooseColoringForVertex(int v, BipartialGraph *bg) {
	//cout << "v: " << v << ", size: " << g.getEdgesNum(v) << endl; 
	
	vector< pair<int, int> > coloring = bg->findMatchingOfSize( g.getEdgesNum(v) ); 
	if (coloring.empty()) {
		//cout << "coloring empty" << endl; 
		return false; 
	}
	
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
		
		cout << g.getColorsNum() << endl; 
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
