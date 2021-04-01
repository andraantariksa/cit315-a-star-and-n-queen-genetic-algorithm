#pragma once

void n_queen(unsigned int n);

class NQueenGenetic {
private:
    int maxFitness;
    unsigned int nQueen;
    std::vector<std::vector<Queen>> population;
    std::vector<int> fitness_pop;
};
