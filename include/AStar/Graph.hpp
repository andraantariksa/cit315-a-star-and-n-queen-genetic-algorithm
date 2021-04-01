#pragma once

#include <unordered_map>

#include <AStar/Edge.hpp>
#include <AStar/ShortestPathAlgorithm.hpp>

class ShortestPathAlgorithm;

class Graph
{
private:
	std::unordered_map<std::string, Coord2D> nodes;
	std::unordered_map<std::string, std::vector<Edge>> edges;
public:
	void addNode(const std::string& name, Coord2D coord);
	// Edge by default are created as a bidirectional
	// Edges node must be registered or exception will be thrown
    // Two ways means bidirectional
	void addEdge(const std::string& nodeFromName, const std::string& nodeToName, float cost, bool twoWays = true);
	std::optional<std::pair<std::vector<std::string>, float>> shortestPath(const std::string& nodeFromName, const std::string& nodeToName, ShortestPathAlgorithm& algorithm);

	// Getter
	const std::unordered_map<std::string, Coord2D>& getNodes() { return nodes; }
    const std::unordered_map<std::string, std::vector<Edge>>& getEdges() { return edges; }
};
