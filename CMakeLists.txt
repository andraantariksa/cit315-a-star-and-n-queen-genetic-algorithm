set(PROJECT_NAME "A Star and N Queen Genetic Algorithm")

cmake_minimum_required(VERSION 3.19)
project(${PROJECT_NAME})

set(A_STAR_HEADERS
	"include/ShortestPathAlgorithm.hpp"
	"include/AStar.hpp"
	"include/Utils.hpp"
	"include/Coord2D.hpp"
	"include/AStar.hpp"
	"include/Edge.hpp"
	"include/Graph.hpp"
	"include/AStarShortestPathAlgorithm.hpp"
	"include/ShortestPathAlgorithm.hpp")
	
set(A_STAR_SOURCES
	"src/main.cpp"
	"src/Utils.cpp"
	"src/AStar.cpp"
	"src/Graph.cpp"
	"src/Edge.cpp"
	"src/AStarShortestPathAlgorithm.cpp")

add_executable("AStar"
	${A_STAR_HEADERS}
	${A_STAR_SOURCES})

target_include_directories("AStar"
	PUBLIC
	"include/")
