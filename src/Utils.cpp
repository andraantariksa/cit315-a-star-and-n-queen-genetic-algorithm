#include <Utils.hpp>
#include <Coord2D.hpp>
#include <cmath>

float EuclideanDistance(Coord2D from, Coord2D to)
{
	int dx = std::abs(from.x - to.x);
	int dy = std::abs(from.y - to.y);
	return sqrtf((float)(dx * dy + dx * dy));
}

float DiagonalDistance(Coord2D from, Coord2D to)
{
	int dx = std::abs(from.x - to.x);
	int dy = std::abs(from.y - to.y);
	return sqrtf((float)(dx * dy + dx * dy)) * std::fminf((float)dx, (float)dy);
}

float ManhattanDistance(Coord2D from, Coord2D to)
{
    return std::abs((float)(from.x - to.x)) + std::abs((float)(from.y - to.y));
}
