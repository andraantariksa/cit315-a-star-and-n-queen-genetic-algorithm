//
// Created by M Nabil Asykar on 4/1/2021.
//
#pragma once
#ifndef CIT315_A_STAR_AND_N_QUEEN_GENETIC_ALGORITHM_POPULATION_H
#define CIT315_A_STAR_AND_N_QUEEN_GENETIC_ALGORITHM_POPULATION_H

#include <Nqueen/Chromosome.hpp>

class Population {
public:
    Population(std::vector<Chromosome> new_chromosomes: chromosomes(new_chromosomes)) {}

    std::vector<Chromosome> chromosomes;
    Chromosome randomPick();
};

#endif //CIT315_A_STAR_AND_N_QUEEN_GENETIC_ALGORITHM_POPULATION_H
