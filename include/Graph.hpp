#pragma once

#include <unordered_map>

#include <Edge.hpp>
#include <ShortestPathAlgorithm.hpp>

class ShortestPathAlgorithm;

class Graph
{
private:
	std::unordered_map<std::string, Coord2D> nodes;
	std::unordered_map<std::string, std::vector<Edge>> edges;
public:
	void addNode(const std::string& name, Coord2D coord);
	void addEdge(const std::string& nodeFromName, const std::string& nodeToName, int cost, bool twoWays);
	void shortestPath(const std::string& nodeFromName, const std::string& nodeToName, ShortestPathAlgorithm& algorithm);

	const std::unordered_map<std::string, Coord2D>& getNodes() { return nodes; }
    const std::unordered_map<std::string, std::vector<Edge>>& getEdges() { return edges; }
};
