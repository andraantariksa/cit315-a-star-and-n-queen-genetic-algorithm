#include <AStarShortestPathAlgorithm.hpp>
#include <set>
#include <optional>
#include <queue>
#include <unordered_map>
#include <map>
#include <iostream>
#include <limits>

struct Node {
    float gScore;
    float fScore;
};

std::optional<std::vector<std::string>> AStarShortestPathAlgorithm::resolve(
    std::string startNode,
    std::string endNode,
    Graph& graph)
{
    std::optional<std::vector<std::string>> result;

    std::unordered_map<std::string, std::string> path;

    auto edges = graph.getEdges();
    auto nodes = graph.getNodes();

    std::unordered_map<std::string, float> gScore;
    std::unordered_map<std::string, float> fScore;
    for (auto& node: nodes)
    {
        gScore[node.first] = std::numeric_limits<float>::infinity();
        fScore[node.first] = std::numeric_limits<float>::infinity();
    }
    gScore[startNode] = 0;
    fScore[startNode] = heuristic(nodes[startNode], nodes[endNode]);

    auto nodeComparator = [fScore](std::string a, std::string b) -> bool {
        return fScore.at(a) > fScore.at(b);
    };
    std::set<std::string, decltype(nodeComparator)> nodesOpened(nodeComparator);
    nodesOpened.insert(startNode);

    while (!nodesOpened.empty())
    {
        const auto& current = *--nodesOpened.cend();
        nodesOpened.erase(nodesOpened.cbegin());
        if (current == endNode)
        {
            return resolvePath(path, current);
        }

        auto& neighborsWay = edges.at(current);
        for (auto& neighborWay : neighborsWay)
        {
            float tentativeScore = gScore[current] + heuristic(nodes[current], nodes[neighborWay.nodeToName]);
            std::cout << "Tentative: " << tentativeScore << '\n';
            if (tentativeScore < gScore[neighborWay.nodeToName])
            {
                path[neighborWay.nodeToName] = current;
                gScore[neighborWay.nodeToName] = tentativeScore;
                fScore[neighborWay.nodeToName] = gScore[neighborWay.nodeToName] + heuristic(nodes[current], nodes[neighborWay.nodeToName]);
                nodesOpened.insert(neighborWay.nodeToName);
            }
        }
    }

    return result;
}

std::vector<std::string> AStarShortestPathAlgorithm::resolvePath(
    std::unordered_map<std::string, std::string>& path,
    std::string currentNode)
{
    std::vector<std::string> pathVector;
    pathVector.push_back(currentNode);
    while (path.find(currentNode) != path.cend())
    {
        currentNode = path[currentNode];
        pathVector.push_back(currentNode);
    }
    std::reverse(pathVector.begin(), pathVector.end());
    std::cout << "Path\n";
    for (auto& node: pathVector)
    {
        std::cout << node << '\n';
    }
    return pathVector;
}
