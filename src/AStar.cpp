#include <functional>
#include <string>
#include <iostream>

#include <Coord2D.hpp>
#include <AStar/Graph.hpp>
#include <AStar.hpp>
#include <AStar/AStarShortestPathAlgorithm.hpp>

// A Star entry function
void a_star(const std::function<float(Coord2D, Coord2D)>& distanceFunction)
{
    Graph graph;

    // Populate nodes
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

    // Populate edges
    std::string nodeNameFrom;
    std::string nodeNameTo;

    {
        float cost;
        unsigned int edgeTotal;

        std::cin >> edgeTotal;
        for (int i = 0; i < edgeTotal; ++i)
        {
            std::cin >> nodeNameFrom >> nodeNameTo >> cost;
            graph.addEdge(nodeNameFrom, nodeNameTo, cost);
        }
    }

    // Set the starting and goal
    std::cin >> nodeNameFrom >> nodeNameTo;

    AStarShortestPathAlgorithm algorithm(distanceFunction);
    auto shortestPathResult = graph.shortestPath(nodeNameFrom, nodeNameTo, algorithm);

    if (shortestPathResult.has_value())
    {
        const auto& shortestPath = shortestPathResult.value();

        std::cout << "Path\n";
        for (auto& node: shortestPath.first)
        {
            std::cout << "- " << node << '\n';
        }
        std::cout << "Cost " << shortestPath.second << '\n';
    }
    else
    {
        std::cout << "No path available or error\n";
    }
}
