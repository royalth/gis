#ifndef BG_HPP
#define BG_HPP

#include "common.hpp"

/**
 * Klasa przedstawiająca pomocniczy graf dwudzielny, zawierająca implementację algorytmu Hopcrofta-Karpa do szukania maksymalnego 
 * skojarzenia w grafie. Algorytm ten jest zmodyfikowany dla potrzeb szukania zwartego kolorowania. 
 */
class BipartialGraph {
	private:
		/** Liczba wierzchołków w lewej stronie grafu - odpowiadają krawędziom oryginalnego grafu. */ 
		int V_l;
		
		/** Liczba wierzchołków w prawej stronie grafu - odpowiadają kolorom krawędzi oryginalnego grafu. */ 
		int V_r;
		
		/** Minimalny wierzchołek lewej strony grafu. */ 
		int min_l; 
		
		/** Maksymalny wierzchołek lewej strony grafu. */ 
		int max_l; 
		
		/** Minimalny wierzchołek prawej strony grafu. */ 
		int min_r; 
		
		/** Maksymalny wierzchołek prawej strony grafu. */ 
		int max_r; 
		
		/** Listy sąsiedztwa dla kolejnych wierzchołków lewej strony grafu. */
		vector<int> edges[MAXV]; 
		
		/** Dopasowane wierzchołki prawej strony grafu dla lewej strony grafu. */ 
		int matching_l[MAXV];
		
		/** Dopasowane wierzchołki lewej strony grafu dla prawej strony grafu. */ 
		int matching_r[MAXV];
		
		/** Tablica odległości od wierzchołka NIL w bfsie/dfsie. */ 
		int dist[MAXV]; 
							
		/**
		 * Metoda wykonująca (wielokrotnie) algorytm Hopcrofta-Karpa, szukająca skojarzenia o rozmiarze size, 
		 * które zawiera ciągły podprzedział wierzchołków prawej strony grafu. Zwraca true, jeśli takie skojarzenie zostało znalezione. 
		 */
		bool hopcroftKarp(int size);
		
		/**
		 * Metoda wykonująca pojedyncze przejście algorytmu Hopcrofta-Karpa, w którym bierze pod uwagę tylko wierzchołki 
		 * prawej strony grafu zawierające się w przedziale [first; last]. 
		 */
		int hopcroftKarpForInterval(int first, int last); 
		
		/**
		 * Metoda wykonująca algorytm przeszukiwania wszerz na potrzeby algorytmu Hopcrofta-Karpa. 
		 */
		bool bfs(int first, int last);
		
		/**
		 * Metoda wykonująca algorytm przeszukiwania wgłąb na potrzeby algorytmu Hopcrofta-Karpa. 
		 */
		bool dfs(int l, int first, int last);
		
	public:
		BipartialGraph(); 
		
		/**
		 * Metoda dodająca krawędź między wierzchołkiem l a r do grafu dwudzielnego. Wierzchołek l jest dodany do lewej strony
		 * grafu, a r - do prawej. 
		 */
		void addEdge(int l, int r);
		
		/**
		 * Metoda szukajaca skojarzenia o danym rozmiarze, z wykorzystaniem algorytmu Hopcrofta-Karpa. Zwraca listę par (krawędź, kolor). 
		 * Jeśli skojarzenie o danym rozmiarze nie zostało znalezione - zwraca pusty wektor. 
		 */  
		vector< pair<int, int> > findMatchingOfSize(int size); 
};

#endif /** BG_HPP */
