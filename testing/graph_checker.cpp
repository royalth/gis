#include "../src/common.hpp"

int N, maxv; 
vector< pair<int, int> > edges[MAXV]; 
bool correct; 

bool cmp(pair<int, int> e1, pair<int, int> e2) {
	return e1.second < e2.second; 
}

void checkNotGreaterThanN(int v, int idx) {
	if (edges[v][idx].second < 1 || edges[v][idx].second > N)  {
		cout << "Krawedz laczaca wierzcholki " << v << " i " << edges[v][idx].first << " o kolorze " << edges[v][idx].second; 
		cout << " jest poza zakresem." << endl; 
		correct = false; 
	}
}

void checkWithPrevious(int v, int idx) {
	if (edges[v][idx].second - edges[v][idx-1].second != 1) {
		cout << "Roznica miedzy kolejnymi krawedziami:"; 
		cout << " (" << v << ", " << edges[v][idx-1].first << ", " << edges[v][idx-1].second << ") i";
		cout << " (" << v << ", " << edges[v][idx].first << ", " << edges[v][idx].second << ") jest rozna od 1." << endl; 
		correct = false; 
	}
}

int main() {
	cin >> N;
	
	int v1, v2, c, maxc = 0, minc = 2000000000; 
	maxv = 0; 
	correct = true; 
	while (cin >> v1 >> v2 >> c) {
		maxv = max(maxv, v1); 
		maxv = max(maxv, v2);
		maxc = max(maxc, c); 
		minc = min(minc, c); 
		edges[v1].push_back(make_pair(v2, c)); 
		edges[v2].push_back(make_pair(v1, c)); 
	}
	
	if (maxc != N) {
		cout << "Najwiekszy kolor w grafie jest różny od podanej liczby wykorzystanych kolorow. " << endl; 
		correct = false; 
	}
	if (minc != 1) {
		cout << "Najmniejszy kolor jest rozny od 1 - jest równy " << minc << endl; 
		correct = false; 
	}
	
	for (int i = 1; i <= maxv; ++i) {
		if (edges[i].empty())
			continue; 
		if (edges[i].size() == 1) {
			checkNotGreaterThanN(i, 0); 
			continue; 
		}
		
		sort(edges[i].begin(), edges[i].end(), cmp); 
		for (int j = 1; j < edges[i].size(); ++j) {
			checkNotGreaterThanN(i, j); 
			checkWithPrevious(i, j); 
		} 
	}
	
	if (correct) 
		cout << "Kolorowanie poprawne!" << endl; 
	
	return 0; 
}
 
