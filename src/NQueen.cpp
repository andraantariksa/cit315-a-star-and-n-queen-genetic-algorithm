#include <NQueen.hpp>
#include <cmath>
#include <vector>
#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <NQueen/Queen.hpp>
#include <NQueen/Chromosome.hpp>
#include <NQueen/Population.hpp>

//int nq, maxFitness;
//std::vector<int> fitness_pop;


class NQueenGenetic
{
public:
    void printChessboard()
    {
        std::vector<std::vector<char>> board(nQueen, std::vector<char>(nQueen, 'X'));

        for (int i = 0; i < nQueen; ++i)
        {
            board[nQueen - solution_chromosome[i].row][i] = 'Q';
        }

        for (auto& row : board)
        {
            for (auto& col : row)
            {
                std::cout << col << '\n';
            }
            std::cout << '\n';
        }
    }

    bool Population::check_fitness(int maxFitness) {
        fitness_pop.clear();
        for (auto chromosome : this->chromosomes) {
            chromosome.calculate_fitness();
            int f = chromosome.fitness;
            fitness_pop.push_back(int(f));
            if (f == maxFitness)
                return false;
        }
        return true;
    }

    void n_queen()
    {
        pop_num = 500;//nq * 5 + 70;
        this->population.chromosomes.reserve(nQueen);

        maxFitness = (nQueen * (nQueen - 1)) / 2;
        for (size_t i = 0; i < pop_num; ++i) {
            Chromosome new_chromosome;
            new_chromosome.random();
            this->population.chromosomes.push_back(new_chromosome);
        }
        int generation = 1;

        while (this->population.check_fitness(maxFitness)) {
    //        printf("=== Generation %d ===\n", generation);
            this->population = genetic_queen(this->population, generation);
    //        printf("\n");
    //        printf("Highest Fitness = %d\n", *max_element(fitness_pop.begin(), fitness_pop.end()));
            generation++;
        }

        Chromosome solution_chromosome;
        printf("Solved in Generation %d!\n", generation - 1);

        auto current_fitness = fitness_pop.begin();
        for (const auto& chromosome : this->population.chromosomes) {
            if (*current_fitness == maxFitness) {
                printf("\nOne of the solutions: ");
                solution_chromosome = chromosome;
                solution_chromosome.print();
                break;
            }
            current_fitness++;
        }

        print_chessboard();
    }

private:
    int nQueen, maxFitness, pop_num;
    Population population;
    vector<int> fitness_pop;

    Population genetic_queen(Population &population, int generation) {
        double mutation_probability = 0.2;
        int num_pop = population.chromosomes.size();
        std::vector<double> weights;
        vector<Chromosome> new_chromosomes;

        weights.reserve(num_pop);
        for (const auto& p : population.chromosomes)
        {
            weights.push_back(double(p.pick_weight(p.calculate_fitness())));
        }

        while (new_chromosomes.size() < population.size()) {
            Chromosome parent_x = population.random_pick(weights);
            Chromosome parent_y = population.random_pick(weights);
            //vector<vector<queen>> children = crossover_1(parent_x, parent_y);
            //vector<queen> &child1 = children[0];
            //vector<queen> &child2 = children[1];
            Chromosome child1;
            Chromosome child2;
            double r = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX));

            if (generation % 2 == 0) {
                std::vector<Chromosome> children = parent_x.crossover_1(parent_y);
                child1 = children[0];
                child2 = children[1];
            }
            else if (generation % 4 == 0) {
                std::vector<Chromosome> children = parent_x.crossover_3(parent_y);
                child1 = children[0];
                child2 = children[1];
            }
            else
            {
                child1 = parent_y.crossover_2(parent_x);
                child2 = parent_x.crossover_2(parent_y);
            }

            if (r < mutation_probability) {
                child1 = child1.mutate();
                child2 = child2.mutate();
            }
            child1.calculate_fitness();
            child2.calculate_fitness();
            //        print_chromosome(child1, fitness_child_1);
            //        print_chromosome(child2, fitness_child_2);
            new_chromosomes.push_back(Chromosome(child1));
            fitness_pop.push_back(child1.fitness);
            new_chromosomes.push_back(Chromosome(child2));
            fitness_pop.push_back(child2.fitness);
            if (child1.fitness == maxFitness || child2.fitness == maxFitness)
                break;
        }
        return Population(chromosomes);
    }
};



void n_queen(unsigned int)
{

}
