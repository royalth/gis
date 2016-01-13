#include <iostream>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <ctime>
using namespace std; 

const int MAXV = 10000; 

int E, V; 
bool alreadyUsed[MAXV][MAXV];

int main() {
	cin >> V >> E; 
	if (E > V*(V-1)/2) {
		cout << "Zbyt duza liczba krawedzi." << endl; 
		return 0; 
	}
	
	cout << V << " " << E << endl; 

	boost::random::uniform_int_distribution<> dist(1, V);
	boost::random::mt19937 gen = boost::random::mt19937(time(NULL)); 
	
	int v1, v2; 
	while (E--) {
		v1 = dist(gen); 
		do {
			v2 = dist(gen); 
		} while (v1 == v2 || alreadyUsed[v1][v2]); 
		
		cout << v1 << " " << v2 << endl; 
		alreadyUsed[v1][v2] = true; 
		alreadyUsed[v2][v1] = true; 
	}
	
	return 0; 
}
