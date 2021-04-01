//
// Created by M Nabil Asykar on 4/1/2021.
//
#pragma once
#include <NQueen/Chromome.hpp>
#include <vector>

int Chromosome::calculate_fitness(int maxFitness)
{
    int conflicts = 0;
    for(int i = 0; i < chromosome.size(); ++i) {
        for (int j = i + 1; j < chromosome.size(); ++j) {
            if (chromosome[i].isConflicted(chromosome[j])) {
                conflicts++;
            }
        }
    }
    this->fitness = int(maxFitness - conflicts);
    return int(maxFitness - conflicts);
}

double Chromosome::pick_weight(int maxFitness)
{
    this->weight = (double) fitness / maxFitness;
    return (double) fitness / maxFitness;
}

void Chromosome::random()
{
    this->genes.clear();
    for (int i = 0; i < nq; i++)
    {
        this->genes.push_back(Queen { rand() % nq + 1, i });
    }
}

void Chromosome::print()
{
    std::cout << "Chromosome = [";
    for (auto& queen : this->genes)
    {
        std::cout << queen.row << "] Fitness = " << this->fitness << '\n';
    }
}

Chromosome mutate() {
    int n = this->genes.size();
    int tuple_size = (n - (n % 3)) / 3;
    int random_idx = rand() % n;
    int random_val = rand() % n + 1;
    int swap_pos = this->genes[random_idx].row;
    this->genes[(random_idx+tuple_size)%n].row = swap_pos;
    this->genes[random_idx].row = random_val;
    return this->genes;
}


std::vector<Chromosome> Chromosome::crossover_1(Chromosome chromosome)
{
    std::vector<Queen> genes_x = this->genes;
    std::vector<Queen> genes_y = chromosome.genes;
    int n = genes_x.size();
    std::vector<Queen> child_1 = this->genes;
    std::vector<Queen> child_2 = genes_y;
    for (int i = 1; i < n; ++i) {
        if (abs(genes_x[i-1].row - genes_x[i].row) < 2) {
            std::swap(child_1[i].row, child_2[i].row);
        }
        if (abs(genes_y[i-1].row - genes_y[i].row) < 2) {
            std::swap(child_1[i].row, child_2[i].row);
        }
    }

    return std::vector<Chromosome> {Chromosome(child_1), Chromosome(child_2)};
}

Chromosome Chromosome::crossover_2 (Chromosome chromosome)
{
    std::vector<Queen> genes_x = this->genes;
    std::vector<Queen> genes_y = chromosome->genes;

    int n = genes_x.size();
    int c = rand() % n;
    int i = 0;

    std::vector<Queen> child;

    for (; i <= c; i++) {
        child.push_back(Queen({genes_x[i].row, i}));
    }
    for (; i < n; i++) {
        child.push_back(Queen({genes_y[i].row, i}));
    }
    return Chromosome(child);
}

std::vector<Chromosome> Chromosome::crossover_3(Chromosome chromosome)
{
    std::vector<Queen> genes_x = this->genes;
    std::vector<Queen> genes_y = chromosome.genes;
    std::vector<Queen> child_1 = this->.genes;
    std::vector<Queen> child_2 = chromosome.genes;

    int n = genes_x.size();
    int tuple_size = (n - (n % 3)) / 3;
    int center_tuple_idx = tuple_size;
    int last_tuple_size = n % tuple_size;
    if (last_tuple_size == 0) last_tuple_size = tuple_size;

    for (int i = 0; i < tuple_size; ++i, ++center_tuple_idx) {
        child_1[center_tuple_idx].row = genes_y[center_tuple_idx].row;
        child_2[center_tuple_idx].row = genes_x[center_tuple_idx].row;
    }
    int last_idx_1 = center_tuple_idx + rand()%(last_tuple_size);
    int last_idx_2 = center_tuple_idx + rand()%(last_tuple_size);
    assert(last_idx_1 < n || last_idx_2 < n);
    child_1[0].row = genes_y[last_idx_1++].row;
    child_2[0].row = genes_x[last_idx_2++].row;
    for (int i = 1; i < tuple_size-1; ++i, ++last_idx_1, ++last_idx_2) {
        assert(center_tuple_idx + last_idx_1%last_tuple_size < n);
        child_1[i].row = genes_y[center_tuple_idx + last_idx_1%last_tuple_size].row;
        child_2[i].row = genes_x[center_tuple_idx + last_idx_2%last_tuple_size].row;
    }

    return std::vector<Chromosome> {Chromosome(child_1), Chromosome(child_2)};
}