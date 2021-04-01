//
// Created by M Nabil Asykar on 4/1/2021.
//
#pragma once
#ifndef CIT315_A_STAR_AND_N_QUEEN_GENETIC_ALGORITHM_CHROMOSOME_H
#define CIT315_A_STAR_AND_N_QUEEN_GENETIC_ALGORITHM_CHROMOSOME_H

#include <vector>

class Chromosome {
public:
    vector<Queen> genes;
    int fitness;
    double weight;

    Chromosome(std::vector<Queen> new_genes) : genes(new_genes){}

    int calculate_fitness();
    double pick_weight(int maxFitness);
    void random();
    void print();
    Chromosome mutate();
    std::vector<Chromosome> crossover_1(Chromosome chromosome);
    Chromosome crossover_2(Chromosome chromosome);
    std::vector<Chromosome> crossover_3(Chromosome chromosome);
};

#endif //CIT315_A_STAR_AND_N_QUEEN_GENETIC_ALGORITHM_CHROMOSOME_H
