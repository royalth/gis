#ifndef GC_HPP
#define GC_HPP

#include "BipartialGraph.hpp"
#include "Graph.hpp"


/**
 * Klasa zawierająca logikę oraz struktury potrzebne do znalezienia kolorowania w grafie. 
 */
class GraphColoring {
	
private: 
	/**
	 * Struktura pomocnicza, która przedstawia przedział liczbowy - możliwy przedział kolorów dla krawędzi danego wierzchołka. 
	 */
	struct Interval {
		Interval() {
			start = 1;
			end = INF; 
		}
		int start, end; 
	}; 
	
	/** Liczba wierzchołków. */
	int V;
	
	/** Liczba krawędzi. */
	int E; 
	
	/** Tablica przedziałów możliwych kolorów krawędzi dla każdego wierzchołka. */
	Interval interval[MAXV];
	
	/** Flaga oznaczająca, czy zostało znalezione kolorowanie. */ 
	bool coloringFound; 
	
	/** Struktura zawierająca budowę grafu. */
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


#endif /** GC_HPP */
