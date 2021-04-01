#include <AStar/AStarShortestPathAlgorithm.hpp>
#include <set>
#include <optional>
#include <queue>
#include <unordered_map>
#include <iostream>
#include <limits>

std::optional<std::pair<std::vector<std::string>, float>> AStarShortestPathAlgorithm::resolve(
    std::string startNode,
    std::string endNode,
    Graph& graph)
{
    std::optional<std::pair<std::vector<std::string>, float>> result;

    // Path of visited node comes from another node
    // Used to trace the shortest path
    std::unordered_map<std::string, PathNode> path;

    auto edges = graph.getEdges();
    auto nodes = graph.getNodes();

    // The cheapest cost (of an edge) to get to the correspond nodes
    std::unordered_map<std::string, float> gScore;
    // f(x) = g(x) + h(x)
    std::unordered_map<std::string, float> fScore;
    for (auto& node: nodes)
    {
        gScore[node.first] = std::numeric_limits<float>::infinity();
        fScore[node.first] = std::numeric_limits<float>::infinity();
    }
    gScore[startNode] = 0; // Starting node has a 0 cost to traverse
    fScore[startNode] = heuristic(nodes[startNode], nodes[endNode]);

    // Comparator for sorting the node based on fScore
    auto nodeComparator = [fScore](std::string a, std::string b) -> bool {
        // To distinguish both string
        if (fScore.at(a) <= fScore.at(b))
        {
            return a != b;
        }

        // To order the node, lesser fScore as latter
        return fScore.at(a) > fScore.at(b);
    };
    std::set<std::string, decltype(nodeComparator)> nodesOpened(nodeComparator);
    nodesOpened.insert(startNode);

    while (!nodesOpened.empty())
    {
        // Pop node with the least fScore from set
        const auto current = std::string(*--nodesOpened.cend());
        nodesOpened.erase(--nodesOpened.cend());
        if (current == endNode)
        {
            // Found path
            return resolvePath(path, current);
        }

        // Get current node neighbors
        auto& neighborsWay = edges.at(current);
        // Looking for the lowest gScore among the neighbors
        for (auto& neighborWay : neighborsWay)
        {
            float tentativeScore = gScore[current] + neighborWay.cost;
            if (tentativeScore < gScore[neighborWay.nodeToName])
            {
                // Set the node to coming from the current node
                path[neighborWay.nodeToName] = PathNode {
                    .nodeName = current,
                    .cost = neighborWay.cost
                };
                gScore[neighborWay.nodeToName] = tentativeScore;
                // f(x) = g(x) + h(x)
                fScore[neighborWay.nodeToName] = gScore[neighborWay.nodeToName] + heuristic(nodes[current], nodes[neighborWay.nodeToName]);
                nodesOpened.insert(neighborWay.nodeToName);
            }
        }
    }

    // Not found
    return result;
}

std::pair<std::vector<std::string>, float> AStarShortestPathAlgorithm::resolvePath(
    std::unordered_map<std::string, PathNode>& path,
    std::string currentNode)
{
    std::vector<std::string> pathVector;
    pathVector.push_back(currentNode);
    float totalCost = 0.0f;
    // Trace back to the starting node. The starting node does not have any predecessor node.
    while (path.find(currentNode) != path.cend())
    {
        const auto& currentPath = path[currentNode];
        totalCost += currentPath.cost;
        // Change the current node
        currentNode = currentPath.nodeName;
        pathVector.push_back(currentNode);
    }
    // The direction should be reversed
    std::reverse(pathVector.begin(), pathVector.end());

    return std::make_pair(pathVector, totalCost);
}
