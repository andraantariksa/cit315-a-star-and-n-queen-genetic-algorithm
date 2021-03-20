#include <cstring>
#include <iostream>
#include <Coord2D.hpp>
#include <ShortestPathAlgorithm.hpp>
#include <functional>
#include <Utils.hpp>
#include <AStar.hpp>

int main(int argc, char** argv)
{
	if (argc > 1)
	{
		if (strcmp(argv[1], "a*") == 0)
		{
            int distanceChoice = std::stoi(argv[2]);
            std::function<float(Coord2D, Coord2D)> f;
            switch (distanceChoice)
            {
            case 1:
                f = EuclideanDistance;
            case 2:
                f = DiagonalDistance;
            case 3:
            default:
                f = ManhattanDistance;
            }
			AStar(f);
		}
		else if (strcmp(argv[1], "genetic") == 0)
		{
			// TODO
			// Genetic();
		}
	}
}
