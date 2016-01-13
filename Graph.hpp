#include "common.hpp"

/**
 * Klasa przechowująca strukturę oryginalnego grafu. 
 */
class Graph {
	
	private:
	
		/** Listy sąsiedztwa dla wszystkich wierzchołków, zawierające również informację o kolorze krawędzi. 
		 * W pair<int, int> first to drugi wierzchołek krawędzi, a second - jej kolor. */ 
		vector< pair<int, int> > edges[MAXV]; 
		
		/** Liczba wierzchołków w grafie. */ 
		int V;
		
		/** Maksymalny kolor krawędzi w grafie. */
		int maxC;
		
	public:
		Graph();
		Graph(int _V);
		
		/**
		 * Metoda kolorująca krawędź (v1, v2) na kolor c. 
		 */
		void colorEdge(int v1, int v2, int c);
		
		/**
		 * Metoda dodająca do grafu krawędź (v1, v2). Przypisywany jest jej kolor 0. 
		 */
		void addEdge(int v1, int v2);
		
		/**
		 * Metoda zwracająca kolor krawędzi (v1, v2). 
		 */ 
		int getEdgeColor(int v1, int v2);
		
		/**
		 * Metoda zwracająca liczbę krawędzi incydentnych z wierzchołkiem v. 
		 */
		int getEdgesNum(int v);
		
		/**
		 * Metoda zwracająca, czy istnieje krawędź miedzy wierzchołkami v1 i v2. 
		 */
		bool edgeExists(int v1, int v2);
		
		/**
		 * Metoda sprawdzająca, czy wierzchołek v jest incydentny z krawędzią w kolorze c. 
		 */
		bool edgeWithColorExists(int v, int c);
		
		/**
		 * Metoda kolorująca jedną z krawędzi pierwszego wierzchołka na kolor numer 1. 
		 */
		void colorFirstEdge(); 
		
		/**
		 * Metoda zwracająca liczbę kolorów w grafie (maksymalny kolor w grafie).
		 */
		int getColorsNum(); 
		
		/**
		 * Metoda zwracająca listę sąsiedztwa wierzchołka v. 
		 */
		vector< pair<int, int> > getEdges(int v); 
};
