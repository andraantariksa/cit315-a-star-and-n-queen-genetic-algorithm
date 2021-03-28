#pragma once

#include <unordered_map>
#include <utility>
#include <vector>
#include <functional>
#include <optional>
#include <string>

#include <ShortestPathAlgorithm.hpp>
#include <Coord2D.hpp>
#include <Graph.hpp>

class AStarShortestPathAlgorithm: public ShortestPathAlgorithm
{
    using ShortestPathAlgorithm::ShortestPathAlgorithm;
private:
    std::vector<std::string> resolvePath(
        std::unordered_map<std::string, std::string>& path,
        std::string currentNode);
    std::optional<std::vector<std::string>> resolve(
        std::string startNode,
        std::string endNode,
        Graph& graph) override;
};
