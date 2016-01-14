#include "BipartialGraph.hpp"

int main() {
	BipartialGraph b; 
	
	int E, l, r, size; 
	cin >> E; 
	while (E--) {
		cin >> l >> r; 
		b.addEdge(l, r); 
	}
	cin >> size; 
	
	vector< pair<int, int> > result = b.findMatchingOfSize(size); 
	cout << result.size() << endl; 
	
	for (vector< pair<int, int> >::iterator it = result.begin(); it != result.end(); ++it) {
		cout << it->first << " " << it->second << endl; 
	}

	return 0; 
}
