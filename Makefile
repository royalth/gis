all: 
	g++ main.cpp GraphColoring.cpp BipartialGraph.cpp Graph.cpp -o gis
	
bipartial_test: bipartial_graph_test.cpp BipartialGraph.hpp BipartialGraph.cpp 
	g++ bipartial_graph_test.cpp BipartialGraph.cpp -o bipartial_test
