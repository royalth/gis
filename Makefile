all: 
	g++ src/main.cpp src/GraphColoring.cpp src/BipartialGraph.cpp src/Graph.cpp -o gis
	
bipartial_test: testing/bipartial_graph_test.cpp src/BipartialGraph.hpp src/BipartialGraph.cpp 
	g++ testing/bipartial_graph_test.cpp src/BipartialGraph.cpp -o bipartial_test
	
checker: testing/graph_checker.cpp
	g++ testing/graph_checker.cpp -o graph_checker
	
test_gen: testing/graph_generator.cpp
	g++ testing/graph_generator.cpp -o test_generator

