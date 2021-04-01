//#include <NQueen.hpp>
//#include <cmath>
//#include <vector>
//#include <cstdio>
//#include <cassert>
//#include <cstdlib>
//#include <iostream>
//#include <algorithm>
//#include <functional>
//#include <numeric>
//#include <NQueen/Queen.hpp>
//
////int nq, maxFitness;
////std::vector<int> fitness_pop;
//
//class Chromosome
//{
//public:
//    Chromosome()
//    {
//
//    }
//private:
//    void random()
//    {
//        chromosome.clear();
//        for (int i = 0; i < nq; i++)
//        {
//            chromosome.push_back(Queen { rand() % nq + 1, i });
//        }
//    }
//
//    void print(int fitness)
//    {
//        std::cout << "Chromosome = [";
//        for (auto& queen : chromosome)
//        {
//            std::cout << queen.row << "] Fitness = " << fitness << '\n';
//        }
//    }
//
//    std::vector<Queen> chromosome;
//};
//
//class NQueenGenetic
//{
//public:
//    void printChessboard()
//    {
//        std::vector<std::vector<char>> board(nQueen, std::vector<char>(nQueen, 'X'));
//
//        for (int i = 0; i < nQueen; ++i)
//        {
//            board[nQueen - solution_chromosome[i].row][i] = 'Q';
//        }
//
//        for (auto& row : board)
//        {
//            for (auto& col : row)
//            {
//                std::cout << col << '\n';
//            }
//            std::cout << '\n';
//        }
//    }
//private:
//    std::vector<Queen> randomPick(
//        std::vector<std::vector<Queen>> &populations,
//        std::vector<double> &weights)
//    {
//        double weightSum = std::accumulate(weights.cbegin(), weights.cend(), 0.0);
//
//        double r = ( static_cast <double> (rand()) / static_cast <double> (RAND_MAX) ) * static_cast<double>(weightSum);
//        double distributed_weights = 0;
//
//        auto population = populations.begin();
//        auto weight = weights.begin()
//        for (; population != populations.end() || weight != weights.end();)
//        {
//            if (r <= distributed_weights + *weight)
//            {
//                return *population;
//            }
//            distributed_weights += *weight;
//
//            ++population;
//            ++weight;
//        }
//
//        assert(false && "Unreachable");
//    }
//
//    double pickWeight(int fitness)
//    {
//        return (double) fitness / maxFitness;
//    }
//
//    int fitness(std::vector<Queen> chromosome)
//    {
//        int conflicts = 0;
//        for(int i = 0; i < chromosome.size(); ++i) {
//            for (int j = i + 1; j < chromosome.size(); ++j) {
//                if (chromosome[i].isConflicted(chromosome[j])) {
//                    conflicts++;
//                }
//            }
//        }
//        return int(maxFitness - conflicts);
//    }
//
//    int maxFitness;
//    unsigned int nQueen;
//};
//
//std::vector<std::vector<Queen>> crossover_1(std::vector<Queen> chromosome_x, std::vector<Queen> chromosome_y)
//{
//    int n = chromosome_x.size();
//    std::vector<Queen> child_1 = chromosome_x;
//    std::vector<Queen> child_2 = chromosome_y;
//    for (int i = 1; i < n; ++i) {
//        if (abs(chromosome_x[i-1].row - chromosome_x[i].row) < 2) {
//            std::swap(child_1[i].row, child_2[i].row);
//        }
//        if (abs(chromosome_y[i-1].row - chromosome_y[i].row) < 2) {
//            std::swap(child_1[i].row, child_2[i].row);
//        }
//    }
//
//    return std::vector<std::vector<Queen>> {child_1, child_2};
//}
//
//std::vector<Queen> crossover_2 (std::vector<Queen> chromosome_x, std::vector<Queen> chromosome_y)
//{
//    int n = chromosome_x.size();
//    int c = rand() % n;
//    int i = 0;
//
//    std::vector<Queen> child;
//
//    for (; i <= c; i++) {
//        child.push_back(Queen({chromosome_x[i].row, i}));
//    }
//    for (; i < n; i++) {
//        child.push_back(Queen({chromosome_y[i].row, i}));
//    }
//    return child;
//}
//
//std::vector<std::vector<Queen>> crossover_3(std::vector<Queen> chromosome_x, std::vector<Queen> chromosome_y)
//{
//    int n = chromosome_x.size();
//    int tuple_size = (n - (n % 3)) / 3;
//    int center_tuple_idx = tuple_size;
//    int last_tuple_size = n % tuple_size;
//    if (last_tuple_size == 0) last_tuple_size = tuple_size;
//    std::vector<Queen> child_1 = chromosome_x;
//    std::vector<Queen> child_2 = chromosome_y;
//
//    for (int i = 0; i < tuple_size; ++i, ++center_tuple_idx) {
//        child_1[center_tuple_idx].row = chromosome_y[center_tuple_idx].row;
//        child_2[center_tuple_idx].row = chromosome_x[center_tuple_idx].row;
//    }
//    int last_idx_1 = center_tuple_idx + rand()%(last_tuple_size);
//    int last_idx_2 = center_tuple_idx + rand()%(last_tuple_size);
//    assert(last_idx_1 < n || last_idx_2 < n);
//    child_1[0].row = chromosome_y[last_idx_1++].row;
//    child_2[0].row = chromosome_x[last_idx_2++].row;
//    for (int i = 1; i < tuple_size-1; ++i, ++last_idx_1, ++last_idx_2) {
//        assert(center_tuple_idx + last_idx_1%last_tuple_size < n);
//        child_1[i].row = chromosome_y[center_tuple_idx + last_idx_1%last_tuple_size].row;
//        child_2[i].row = chromosome_x[center_tuple_idx + last_idx_2%last_tuple_size].row;
//    }
//
//    return std::vector<std::vector<Queen>> {child_1, child_2};
//}
//
//
//std::vector<Queen> mutate(std::vector<Queen> chromosome) {
//    int n = chromosome.size();
//    int tuple_size = (n - (n % 3)) / 3;
//    int random_idx = rand() % n;
//    int random_val = rand() % n + 1;
//    int swap_pos = chromosome[random_idx].row;
//    chromosome[(random_idx+tuple_size)%n].row = swap_pos;
//    chromosome[random_idx].row = random_val;
//    return chromosome;
//}
//
//std::vector<std::vector<Queen>> selection(std::vector<std::vector<Queen>> population) {
//    std::vector<std::vector<Queen>> new_population;
//    while (new_population.size() < nq * 3) {
//        auto iter_highestFitness = std::max_element(fitness_pop.begin(), fitness_pop.end());
//        int idx_highestFitness = distance(fitness_pop.begin(), iter_highestFitness);
//        new_population.push_back(population[idx_highestFitness]);
//        fitness_pop.erase(fitness_pop.begin() + idx_highestFitness);
//        population.erase(population.begin() + idx_highestFitness);
//    }
//    return new_population;
//
//}
//
//
//std::vector<std::vector<Queen>> genetic_queen(std::vector<std::vector<Queen>> &population, int generation) {
//    double mutation_probability = 0.2;
//    int num_pop = population.size();
//    std::vector<double> probabilities;
//    std::vector<std::vector<Queen>> new_population = population;
//
//    probabilities.reserve(num_pop);
//    for (const auto& p : population)
//    {
//        probabilities.push_back(double(pick_weight(fitness(p)) ));
//    }
//
//    while (new_population.size() < population.size() * 2) {
//        std::vector<Queen> parent_x = random_pick(population, probabilities);
//        std::vector<Queen> parent_y = random_pick(population, probabilities);
//        //vector<vector<queen>> children = crossover_1(parent_x, parent_y);
//        //vector<queen> &child1 = children[0];
//        //vector<queen> &child2 = children[1];
//        std::vector<Queen> child1;
//        std::vector<Queen> child2;
//        double r = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX));
//
//        if (generation % 2 == 0) {
//            std::vector<std::vector<Queen>> children = crossover_1(parent_x, parent_y);
//            child1 = children[0];
//            child2 = children[1];
//        }
//        else if (generation % 6 == 0) {
//            std::vector<std::vector<Queen>> children = crossover_3(parent_x, parent_y);
//            child1 = children[0];
//            child2 = children[1];
//        }
//        else
//        {
//            child1 = crossover_2(parent_y, parent_x);
//            child2 = crossover_2(parent_x, parent_y);
//        }
//
//        if (r < mutation_probability) {
//            child1 = mutate(child1);
//            child2 = mutate(child2);
//        }
//        int fitness_child_1 = fitness(child1);
//        int fitness_child_2 = fitness(child2);
////        print_chromosome(child1, fitness_child_1);
////        print_chromosome(child2, fitness_child_2);
//        new_population.push_back(std::vector<Queen>(child1));
//        fitness_pop.push_back(fitness_child_1);
//        new_population.push_back(std::vector<Queen>(child2));
//        fitness_pop.push_back(fitness_child_2);
//        if (fitness_child_1 == maxFitness || fitness_child_2 == maxFitness)
//            break;
//    }
//    new_population = selection(new_population);
//    return new_population;
//}
//
//bool check_fitness_population(std::vector<std::vector<Queen>> &population) {
//    fitness_pop.clear();
//    for (auto chromosome : population) {
//        int f = fitness(chromosome);
//        fitness_pop.push_back(int(f));
//        if (f == maxFitness)
//            return false;
//    }
//    return true;
//}
//
//void n_queen()
//{
//    std::vector<std::vector<Queen>> population;
//
//    int pop_num = 500;//nq * 5 + 70;
//    population.reserve(nq);
//
//    maxFitness = (nq * (nq - 1)) / 2;
//    for (size_t i = 0; i < pop_num; ++i) {
//        population.push_back(std::vector<Queen>(random_chromosome(nq)));
//    }
//    int generation = 1;
//
//    while (check_fitness_population(population)) {
////        printf("=== Generation %d ===\n", generation);
//        population = genetic_queen(population, generation);
////        printf("\n");
////        printf("Highest Fitness = %d\n", *max_element(fitness_pop.begin(), fitness_pop.end()));
//        generation++;
//    }
//
//    std::vector<Queen> solution_chromosome;
//    printf("Solved in Generation %d!\n", generation - 1);
//
//    auto current_fitness = fitness_pop.begin();
//    for (const auto& chromosome : population) {
//        if (*current_fitness == maxFitness) {
//            printf("\nOne of the solutions: ");
//            solution_chromosome = chromosome;
//            print_chromosome(solution_chromosome, *current_fitness);
//            break;
//        }
//        current_fitness++;
//    }
//
//    print_chessboard(nq);
//}

void n_queen(unsigned int)
{

}
