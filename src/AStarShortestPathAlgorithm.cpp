#include <AStarShortestPathAlgorithm.hpp>
#include <iostream>

std::vector <std::string> AStarShortestPathAlgorithm::resolve(Graph& graph)
{
    std::vector<std::string> path;

    auto edges = graph.getEdges();
    auto nodes = graph.getNodes();

    std::cout << edges.size() << '\n';

    return path;
}
