#pragma once

#include <unordered_map>
#include <utility>
#include <vector>
#include <functional>
#include <optional>
#include <string>

#include <AStar/ShortestPathAlgorithm.hpp>
#include <Coord2D.hpp>
#include <AStar/Graph.hpp>

struct PathNode
{
    std::string nodeName;
    float cost;
};

class AStarShortestPathAlgorithm: public ShortestPathAlgorithm
{
    using ShortestPathAlgorithm::ShortestPathAlgorithm;
private:
    // Trace shortest path from the ending node
    std::pair<std::vector<std::string>, float> resolvePath(
        std::unordered_map<std::string, PathNode>& path,
        std::string currentNode);
    // None value means there is an error or no path available
    // First represents the path
    // Second represents the cost of the path
    std::optional<std::pair<std::vector<std::string>, float>> resolve(
        std::string startNode,
        std::string endNode,
        Graph& graph) override;
};
