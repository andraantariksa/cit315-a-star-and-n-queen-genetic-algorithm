#pragma once

#include <unordered_map>
#include <utility>
#include <vector>
#include <functional>

#include <ShortestPathAlgorithm.hpp>
#include <Coord2D.hpp>
#include <Graph.hpp>

class AStarShortestPathAlgorithm: public ShortestPathAlgorithm
{
    using ShortestPathAlgorithm::ShortestPathAlgorithm;
private:
    std::vector<std::string> resolve(Graph& graph) override;
};
