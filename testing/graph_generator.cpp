#include "../src/common.hpp"
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <ctime>

int E, V; 
bool alreadyUsed[MAXV][MAXV], isConnected; 
int parent[MAXV];


int find(int x) {
	if (parent[x] == x)
		return x; 
	return find(parent[x]); 
}

void unionn(int x, int y) {
	parent[find(y)] = find(x); 
}

int main() {
	cin >> V >> E; 
	if (E > V*(V-1)/2) {
		cout << "Zbyt duza liczba krawedzi." << endl; 
		return 0; 
	}
	
	if (E < V-1) {
		cout << "Zbyt mala liczba krawedzi." << endl; 
		return 0; 
	}
	
	cout << V << " " << E << endl; 

	boost::random::uniform_int_distribution<> dist(1, V);
	boost::random::mt19937 gen = boost::random::mt19937(time(NULL)); 
	
	for (int i = 1; i <= V; ++i) {
		parent[i] = i; 
	}
	
	int v1, v2; 
	for (int i = 1; i <= E; ++i) {
		do {
			v1 = dist(gen); 
			v2 = dist(gen); 
		} while (v1 == v2 || alreadyUsed[v1][v2] || (i < V && find(v1) == find(v2)) ); 
		
		cout << v1 << " " << v2 << endl; 
		unionn(v1, v2); 
		alreadyUsed[v1][v2] = true; 
		alreadyUsed[v2][v1] = true; 
	} 

	return 0; 
}
