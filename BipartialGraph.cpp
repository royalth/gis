#include "BipartialGraph.hpp" 

vector< pair<int, int> > BipartialGraph::findMatchingOfSize(int size) {
	vector< pair<int, int> > result; 

	//cout << "size: " << size << " min_l: " << min_l << " max_l: " << max_l << " min_r: " << min_r << " max_r: " << max_r << endl; 
	for (int i = min_l; i <= max_l; ++i) {
		//cout << "edges[" << i << "]: "; 
		//for(vector<int>::iterator it = edges[i].begin(); it != edges[i].end(); ++it) {
			//cout << *it << " "; 
		//}
	}
	
	if (!hopcroftKarp(size)) {
		return result; 
	}
	
	for (int i = min_l; i <= max_l; ++i) {
		if (!edges[i].empty())
			result.push_back( make_pair(i, matching_l[i]) ); 
	}
	return result; 
}

bool BipartialGraph::hopcroftKarp(int size) {
	for (int i = min_r; i <= max_r-size+1; ++i) {		
		if (hopcroftKarpForInterval(i, i+size-1) == size)
			return true;
	}
	return false; 
}


int BipartialGraph::hopcroftKarpForInterval(int first, int last) {
	for (int i = min_l; i <= max_l; ++i)
		matching_l[i] = NIL; 				// dopasowania dla wierzchołków lewej strony
	for (int i = first; i <= last; ++i) 
		matching_r[i] = NIL; 				// dopasowania dla wierzchołków prawej strony
	int result = 0; 						// rozmiar skojarzenia 
	
	while (bfs(first, last)) {	// póki znajdujemy ścieżkę powiększającą
		for (int l = min_l; l <= max_l; ++l) {
			if (!edges[l].empty() && matching_l[l] == NIL && dfs(l, first, last))	// jeśli l jest wolnym wierzchołkiem i ścieżka pow. z niego istnieje
				result++; 	// każda ścieżka powiększająca zwiększa rozmiar skojarzenia o 1
		}
	}
	
	return result; 
}

bool BipartialGraph::bfs(int first, int last) {
	queue<int> q; 		// kolejka bfs; będą w niej tylko wierzchołki lewej strony
		
	for (int l = min_l; l <= max_l; ++l) {
		if (edges[l].empty())
			continue; 
		
		if (matching_l[l] == NIL) {			// uzupełniamy kolejkę niedopasowanymi wierzchołkami lewej strony grafu
			dist[l] = 0; 					
			q.push(l); 
		} else {
			dist[l] = INF; 
		}
	}
	
	dist[NIL] = INF; 	// szukamy drogi do dummy wierzchołka NIL
	
	while (!q.empty()) {
		int l = q.front(); 
		q.pop(); 
		
		if (dist[l] < dist[NIL]) {
			for (vector<int>::iterator it = edges[l].begin(); it != edges[l].end(); ++it) {		// iteracja po wierzchołkach do których dojdziemy z l
				if (*it < first || *it > last)		// ograniczamy przedział wierzchołków prawej strony grafu
					continue; 
				
				int l2 = matching_r[*it]; 			// krawędzi l -> r -> l2
				if (dist[l2] == INF) {
					dist[l2] = dist[l] + 1; 
					q.push(l2); 
				}
			}
		}
		
	}
	
	return dist[NIL] != INF; 	// czy udało się znaleźć ścieżkę powiększającą - ścieżkę do wierzchołka NIL
}

bool BipartialGraph::dfs(int l, int first, int last) {
	if (l == NIL)
		return true; 
		
	for (vector<int>::iterator it = edges[l].begin(); it != edges[l].end(); ++it) {
		if (*it < first || *it > last)
			continue; 
		
		int r = *it;	
		int l2 = matching_r[r];				// krawędzi: l -> r -> l2 
		
		if (dist[l2] == dist[l] + 1) {		// jeśli w bfsie przeszliśmy l -> r -> l2 
			
			if (dfs(l2, first, last)) {		// jeśli istnieje ścieżka powiększająca z l2
				matching_l[l] = r; 			// przypisujemy ten fragment ścieżki powiększającej do skojarzenia
				matching_r[r] = l; 
				return true; 
			}
		
		}
	}
	
	// nie ma ścieżki powiększającej z l
	dist[l] = INF; 
	return false; 
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

