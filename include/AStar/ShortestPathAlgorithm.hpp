#pragma once

#include <unordered_map>
#include <utility>
#include <vector>
#include <functional>
#include <Coord2D.hpp>
#include <AStar/Graph.hpp>
#include <optional>

class Graph;

class ShortestPathAlgorithm
{
public:
    // User can specify the heuristic function to the algorithm
	explicit ShortestPathAlgorithm(std::function<float(Coord2D, Coord2D)> heuristic):
		heuristic(std::move(heuristic))
	{
	}

    virtual std::optional<std::pair<std::vector<std::string>, float>> resolve(std::string startNode,
std::string endNode,
Graph& graph) = 0;
protected:
	std::function<float(Coord2D, Coord2D)> heuristic;
};
