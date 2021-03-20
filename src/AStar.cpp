#include <functional>
#include <string>
#include <iostream>

#include <Coord2D.hpp>
#include <Graph.hpp>
#include <AStar.hpp>
#include <AStarShortestPathAlgorithm.hpp>

void AStar(const std::function<float(Coord2D, Coord2D)>& distanceFunction)
{
    Graph graph;

    {
        std::string nodeName;
        Coord2D coord{};
        unsigned int nodeTotal;

        std::cin >> nodeTotal;
        for (int i = 0; i < nodeTotal; ++i)
        {
            std::cin >> nodeName >> coord.x >> coord.y;
            graph.addNode(nodeName, coord);
        }
    }

    std::string nodeNameFrom;
    std::string nodeNameTo;

    {
        int cost;
        unsigned int edgeTotal;

        std::cin >> edgeTotal;
        for (int i = 0; i < edgeTotal; ++i)
        {
            std::cin >> nodeNameFrom >> nodeNameTo >> cost;
            graph.addEdge(nodeNameFrom, nodeNameTo, cost);
        }
    }

    AStarShortestPathAlgorithm algorithm(distanceFunction);
    graph.shortestPath(nodeNameFrom, nodeNameTo, algorithm);
}
