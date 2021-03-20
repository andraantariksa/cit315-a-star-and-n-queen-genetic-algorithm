#pragma once

#include <unordered_map>
#include <utility>
#include <vector>
#include <functional>
#include <Coord2D.hpp>
#include <Graph.hpp>

class Graph;

class ShortestPathAlgorithm
{
public:
	explicit ShortestPathAlgorithm(std::function<float(Coord2D, Coord2D)> heuristic):
		heuristic(std::move(heuristic))
	{
	}

protected:
	std::function<float(Coord2D, Coord2D)> heuristic;

	virtual std::vector<std::string> resolve(Graph& graph) = 0;
};
