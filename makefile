priceGraph: priceGraph.cpp pbPlots.cpp supportLib.cpp
	g++ priceGraph.cpp pbPlots.cpp supportLib.cpp -lm -o priceGraph
	./priceGraph
