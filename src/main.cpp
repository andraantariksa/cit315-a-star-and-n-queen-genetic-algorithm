#include <cstring>
#include <iostream>
#include <Coord2D.hpp>
#include <AStar/ShortestPathAlgorithm.hpp>
#include <NQueen.hpp>
#include <functional>
#include <Utils.hpp>
#include <AStar.hpp>

int main(int argc, char** argv)
{
	if (argc > 1)
	{
		if (strcmp(argv[1], "astar") == 0)
		{
            int distanceChoice = std::stoi(argv[2]);
            std::function<float(Coord2D, Coord2D)> f;
            switch (distanceChoice)
            {
            case 1:
                f = EuclideanDistance;
                break;
            case 2:
                f = DiagonalDistance;
                break;
            case 3:
            default:
                f = ManhattanDistance;
            }
            a_star(f);
		}
		else if (strcmp(argv[1], "nqueen") == 0)
		{
            int n = std::stoi(argv[2]);
            n_queen(n);
		}
	}
}
