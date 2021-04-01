set(PROJECT_NAME "A Star and N Queen Genetic Algorithm")
set(CMAKE_CXX_STANDARD 17)

cmake_minimum_required(VERSION 3.19)
project(${PROJECT_NAME})

set(A_STAR_AND_NQUEEN_GENETIC_HEADERS
	"include/AStar.hpp"
	"include/AStar/Edge.hpp"
	"include/AStar/Graph.hpp"
	"include/AStar/AStarShortestPathAlgorithm.hpp"
	"include/AStar/ShortestPathAlgorithm.hpp"

	"include/NQueen.hpp"
	"include/NQueen/Queen.hpp"

	"include/Utils.hpp"
	"include/Coord2D.hpp")
	
set(A_STAR_AND_NQUEEN_GENETIC_SOURCES
	"src/AStar.cpp"
	"src/AStar/Graph.cpp"
	"src/AStar/AStarShortestPathAlgorithm.cpp"

	"src/NQueen.cpp"
	"src/NQueen/Queen.cpp"

	"src/main.cpp"
	"src/Utils.cpp")

add_executable("AStarAndNQueenGeneticAlgorithm"
	${A_STAR_AND_NQUEEN_GENETIC_HEADERS}
	${A_STAR_AND_NQUEEN_GENETIC_SOURCES})

target_include_directories("AStarAndNQueenGeneticAlgorithm"
	PUBLIC
	"include/")
