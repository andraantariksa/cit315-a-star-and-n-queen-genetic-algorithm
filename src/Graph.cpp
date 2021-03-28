#include <string>

#include <ShortestPathAlgorithm.hpp>
#include <Graph.hpp>
#include <Coord2D.hpp>

void Graph::addNode(const std::string& name, Coord2D coord)
{
    nodes.insert({ name, coord });
    edges.insert({ name, std::vector<Edge>(0) });
}

void Graph::addEdge(const std::string& nodeFromName, const std::string& nodeToName, int cost, bool twoWays)
{
    edges
        .at(nodeFromName)
        .push_back(Edge{
            .nodeToName = nodeToName,
            .cost = cost
        });
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

void Graph::shortestPath(const std::string& nodeFromName,
    const std::string& nodeToName,
    ShortestPathAlgorithm& algorithm)
{
    algorithm.resolve(nodeFromName, nodeToName, *this);
}
