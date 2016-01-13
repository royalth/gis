#ifndef GC_HPP
#define GC_HPP

#include "BipartialGraph.hpp"

class GraphColoring {
	
private: 
	struct Interval {
		Interval() {
			start = 1;
			end = INF; 
		}
		int start, end; 
	}; 
	
	class Graph {
		private:
			int edges[MAXV][MAXV]; 		// -1 - nie ma krawędzi; 0 - jest krawedz, bez przyporzadkowanego koloru; >0 - kolor krawędzi
			int V; 
		public:
			Graph() { } 
			Graph(int _V) : V(_V) {
				for (int i = 0; i <= V; ++i) 
					for (int j = 0; j <= V; ++j) 
						colorEdge(i, j, -1); 
			} 
			void colorEdge(int v1, int v2, int c) {
				edges[v1][v2] = c;
				edges[v2][v1] = c; 
			}
			void addEdge(int v1, int v2) {
				colorEdge(v1, v2, 0); 
			}
			int getEdgeColor(int v1, int v2) {
				return edges[v1][v2]; 
			}
			int getEdgesNum(int v) {
				int num = 0; 
				for (int i = 1; i <= V; ++i)
					if (edges[v][i] >= 0) 
						num++; 
				return num; 
			}
			bool edgeExists(int v1, int v2) {
				return edges[v1][v2] > -1; 
			}
			bool edgeWithColorExists(int v, int c) {
				for (int v2 = 1; v2 <= V; ++v2)
					if (edges[v][v2] == c)
						return true; 

				return false; 
			}
	};

	int V, E, N; 
	Interval interval[MAXV];
	bool coloringFound; 
	Graph g; 


	/**
	 * Zwraca true, jeśli można wykluczyć ten graf - jest on grafem pełnym o nieparzystej liczbie wierzchołków
	 * lub cyklem o nieparzystej liczbie wierzchołków. 
	 */
	bool canExclude();

	/**
	 * Główna pętla heurystyki. Zwraca true tylko, jeśli zostało znalezione jakies przyporządkowanie kolorów. 
	 */
	bool heuristic();

	/**
	 * Przetworzenie pojedynczego wierzchołka w ramach algorytmu. 
	 * Najpierw ogarniczany jest przedział możliwych kolorów dla tego wierzchołka - na podstawie krawędzi 
	 * incydentnych z tym wierzchołkiem, dla których jest już okreslony kolor. 
	 * Następnie przetwarzane są kolejne krawędzie tego wierzchołka. 
	 * Na koniec na podstawie tych informacji wybierane jest pewne kolorowanie krawędzi tego wierzchołka. 
	 */
	bool processVertex(int v);

	/**
	 * Przetwarzanie pojedynczej krawędzi incydentnej z przetwarzanym wierzchołkiem (v1). 
	 * Najpierw ograniczany jest przedział możliwych kolorów dla drugiego incydentnego z nią wierzchołka, 
	 * następnie wybierane są możliwe kolory i zapisywane w pomocniczym grafie dwudzielnym (jeśli udało się jakiekolwiek
	 * możliwe kolory znaleźć). 
	 */
	bool processEdge(int v1, int v2, BipartialGraph *bg);

	/**
	 * Ograniczanie przedziału mozliwych kolorów dla wierzchołka. Przeglądane są wszystkie krawędzie 
	 * wierzchołka i jeśli mają juz przyporządkowany kolor, to przedział jest ograniczany na tej podstawie. 
	 */
	bool limitInterval(int v);

	/**
	 * Tworzy listę możliwych kolorów dla krawędzi między wierzchołkami v1 i v2 na podstawie ich przedziałów oraz już 
	 * pokolorowanych krawędzi tych wierzchołków. 
	 */
	vector<int> getPossibleColors(int v1, int v2);

	/**
	 * Wybór pewnego przyporządkowania kolorów dla krawędzi incydentnych z danym wierzchołkiem. 
	 * Możliwe kolory są przyporządkowane do krawędzi w grafie dwudzielnym, szukane jest maksymalne skojarzenie
	 * w tym grafie algorytmem Hopcrofta-Karpa.
	 */
	bool chooseColoringForVertex(int v, BipartialGraph *bg); 

public:
	GraphColoring(); 
	
	/**
	 * Wczytanie grafu. 
	 */
	void input(); 
	
	/**
	 * Wypisanie wyniku szukania kolorowania: kolorowanie albo komunikat o tym, że nie zostało ono znalezione. 
	 */
	void output(); 
	
	/**
	 * Metoda szukająca kolorowania grafu, zapisująca je w grafie, jeśli zostało znalezione. 
	 */
	void findColoring();
};


#endif // GC_HPP
