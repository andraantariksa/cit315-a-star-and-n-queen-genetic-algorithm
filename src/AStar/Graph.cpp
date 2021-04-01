#include <string>
#include <iostream>
#include <AStar/ShortestPathAlgorithm.hpp>
#include <AStar/Graph.hpp>
#include <Coord2D.hpp>

void Graph::addNode(const std::string& name, Coord2D coord)
{
    nodes.insert({ name, coord });
    edges.insert({ name, std::vector<Edge>(0) });
}

void Graph::addEdge(const std::string& nodeFromName, const std::string& nodeToName, float cost, bool twoWays)
{
    edges
        .at(nodeFromName)
        .push_back(Edge{
            .nodeToName = nodeToName,
            .cost = cost
        });

    // Bidirectional
    if (twoWays)
    {
        edges
            .at(nodeToName)
            .push_back(Edge{
                .nodeToName = nodeFromName,
                .cost = cost
            });
    }
}

std::optional<std::pair<std::vector<std::string>, float>> Graph::shortestPath(
    const std::string& nodeFromName,
    const std::string& nodeToName,
    ShortestPathAlgorithm& algorithm)
{
    return algorithm.resolve(nodeFromName, nodeToName, *this);
}
