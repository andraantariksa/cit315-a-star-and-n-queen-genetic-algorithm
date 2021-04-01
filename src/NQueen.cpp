#include <bits/stdc++.h>

using namespace std;

class queen {
public:
    int row, col;
    queen(int r, int c) : row(r), col(c) {}
    bool isConflicted(queen q) const {
        return (this->row == q.row || this->col == q.col || abs(this->row - q.row) == abs(this->col - q.col));
    }
};


int nq, maxFitness;
vector<int> fitness_pop;

vector<queen> random_chromosome (int size)
{
    vector<queen> chromosome;
    chromosome.reserve(nq);

    for (int i = 0; i < nq; i++)
    {
        chromosome.push_back(queen({rand() % nq + 1, i}));
    }

    return chromosome;
}

void print_chromosome(const vector<queen> &chromosome, int fitness) {
    printf("Chromosome = [");
    for (auto queen = chromosome.begin(); queen != chromosome.end(); ++queen) {
        printf("%d", queen->row);
        if (queen+1 != chromosome.end())
            printf(" ");
        else
            printf("] Fitness = %d\n", fitness);
    }
}

int sum (vector<int> a) {
    int s = 0;
    for (int i = 0; i < nq; ++i)
    {
        s += a[i];
    }

    return s;
}



int fitness(vector<queen> chromosome) {
    int conflicts = 0;
    for(int i = 0; i < chromosome.size(); ++i) {
        for (int j = i + 1; j < chromosome.size(); ++j) {
            if (chromosome[i].isConflicted(chromosome[j])) {
                conflicts++;
            }
        }
    }
    return int(maxFitness - conflicts);
}

double pick_weight (int fitness) {
    return (double)fitness / maxFitness;
}

vector<queen> random_pick(vector<vector<queen>> &population,
    vector<double> &weights) {
    double sum = 0.0;
    for (double w : weights)
    {
        sum += w;
    }
    double r = ( static_cast <double> (rand()) / static_cast <double> (RAND_MAX) ) * static_cast<double>(sum);
    double distributed_weights = 0;
    auto pop = population.begin();
    for (auto weight_choice = weights.begin(); pop != population.end(); ++pop, ++weight_choice) {
        if (r <= distributed_weights + *weight_choice) {
            return *pop;
        }
        distributed_weights += *weight_choice;
    }
    assert(false);
}

vector<vector<queen>> crossover_1 (vector<queen> chromosome_x, vector<queen> chromosome_y) {
    int n = chromosome_x.size();
    vector<queen> child_1 = chromosome_x;
    vector<queen> child_2 = chromosome_y;
    for (int i = 1; i < n; ++i) {
        if (abs(chromosome_x[i-1].row - chromosome_x[i].row) < 2) {
            swap(child_1[i].row, child_2[i].row);
        }
        if (abs(chromosome_y[i-1].row - chromosome_y[i].row) < 2) {
            swap(child_1[i].row, child_2[i].row);
        }
    }

    return vector<vector<queen>> {child_1, child_2};
}

vector<queen> crossover_2 (vector<queen> chromosome_x, vector<queen> chromosome_y) {
    int n = chromosome_x.size();
    int c = rand() % n;
    int i = 0;

    vector<queen> child;

    for (; i <= c; i++) {
        child.push_back(queen({chromosome_x[i].row, i}));
    }
    for (; i < n; i++) {
        child.push_back(queen({chromosome_y[i].row, i}));
    }
    return child;
}

vector<vector<queen>> crossover_3(vector<queen> chromosome_x, vector<queen> chromosome_y) {
    int n = chromosome_x.size();
    int tuple_size = (n - (n % 3)) / 3;
    int center_tuple_idx = tuple_size;
    int last_tuple_size = n % tuple_size;
    if (last_tuple_size == 0) last_tuple_size = tuple_size;
    vector<queen> child_1 = chromosome_x;
    vector<queen> child_2 = chromosome_y;

    for (int i = 0; i < tuple_size; ++i, ++center_tuple_idx) {
        child_1[center_tuple_idx].row = chromosome_y[center_tuple_idx].row;
        child_2[center_tuple_idx].row = chromosome_x[center_tuple_idx].row;
    }
    int last_idx_1 = center_tuple_idx + rand()%(last_tuple_size);
    int last_idx_2 = center_tuple_idx + rand()%(last_tuple_size);
    assert(last_idx_1 < n || last_idx_2 < n);
    child_1[0].row = chromosome_y[last_idx_1++].row;
    child_2[0].row = chromosome_x[last_idx_2++].row;
    for (int i = 1; i < tuple_size-1; ++i, ++last_idx_1, ++last_idx_2) {
        assert(center_tuple_idx + last_idx_1%last_tuple_size < n);
        child_1[i].row = chromosome_y[center_tuple_idx + last_idx_1%last_tuple_size].row;
        child_2[i].row = chromosome_x[center_tuple_idx + last_idx_2%last_tuple_size].row;
    }

    return vector<vector<queen>> {child_1, child_2};
}


vector<queen> mutate(vector<queen> chromosome) {
    int n = chromosome.size();
    int tuple_size = (n - (n % 3)) / 3;
    int random_idx = rand() % n;
    int random_val = rand() % n + 1;
    int swap_pos = chromosome[random_idx].row;
    chromosome[(random_idx+tuple_size)%n].row = swap_pos;
    chromosome[random_idx].row = random_val;
    return chromosome;
}

vector<vector<queen>> selection(vector<vector<queen>> population) {
    vector<vector<queen>> new_population;
    while (new_population.size() < nq * 3) {
        auto iter_highestFitness = max_element(fitness_pop.begin(), fitness_pop.end());
        int idx_highestFitness = distance(fitness_pop.begin(), iter_highestFitness);
        new_population.push_back(population[idx_highestFitness]);
        fitness_pop.erase(fitness_pop.begin() + idx_highestFitness);
        population.erase(population.begin() + idx_highestFitness);
    }
    return new_population;

}


vector<vector<queen>> genetic_queen(vector<vector<queen>> &population, int generation) {
    double mutation_probability = 0.2;
    int num_pop = population.size();
    vector<double> probabilities;
    vector<vector<queen>> new_population;

    probabilities.reserve(num_pop);
    for (const auto& p : population) {
        probabilities.push_back(double(pick_weight(fitness(p)) ));
    }

    while (new_population.size() < population.size()) {
        vector<queen> parent_x = random_pick(population, probabilities);
        vector<queen> parent_y = random_pick(population, probabilities);
        //vector<vector<queen>> children = crossover_1(parent_x, parent_y);
        //vector<queen> &child1 = children[0];
        //vector<queen> &child2 = children[1];
        vector<queen> child1;
        vector<queen> child2;
        double r = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX));

        if (generation % 2 == 0) {
            vector<vector<queen>> children = crossover_1(parent_x, parent_y);
            child1 = children[0];
            child2 = children[1];
        }
        else if (generation % 4 == 0) {
            vector<vector<queen>> children = crossover_3(parent_x, parent_y);
            child1 = children[0];
            child2 = children[1];
        }
        else
        {
            child1 = crossover_2(parent_y, parent_x);
            child2 = crossover_2(parent_x, parent_y);
        }

        if (r < mutation_probability) {
            child1 = mutate(child1);
            child2 = mutate(child2);
        }
        int fitness_child_1 = fitness(child1);
        int fitness_child_2 = fitness(child2);
//        print_chromosome(child1, fitness_child_1);
//        print_chromosome(child2, fitness_child_2);
        new_population.push_back(vector<queen>(child1));
        fitness_pop.push_back(fitness_child_1);
        new_population.push_back(vector<queen>(child2));
        fitness_pop.push_back(fitness_child_2);
        if (fitness_child_1 == maxFitness || fitness_child_2 == maxFitness)
            break;
    }
//    new_population = selection(new_population);
    return new_population;
}

bool check_fitness_population(vector<vector<queen>> &population) {
    fitness_pop.clear();
    for (auto chromosome : population) {
        int f = fitness(chromosome);
        fitness_pop.push_back(int(f));
        if (f == maxFitness)
            return false;
    }
    return true;
}

void n_queen(unsigned int total_queen)
{
    srand (static_cast <unsigned> (time(0)));
    vector<vector<queen>> population;

    nq = total_queen;
    int pop_num = 500;//nq * 5 + 70;
    population.reserve(nq);

    maxFitness = (nq * (nq - 1)) / 2;
    for (size_t i = 0; i < pop_num; ++i) {
        population.push_back(vector<queen> (random_chromosome(nq)));
    }
    int generation = 1;

    while (check_fitness_population(population)) {
//        printf("=== Generation %d ===\n", generation);
        population = genetic_queen(population, generation);
//        printf("\n");
//        printf("Highest Fitness = %d\n", *max_element(fitness_pop.begin(), fitness_pop.end()));
        generation++;
    }

    vector<queen> solution_chromosome;
    printf("Solved in Generation %d!\n", generation - 1);

    auto current_fitness = fitness_pop.begin();
    for (const auto& chromosome : population) {
        if (*current_fitness == maxFitness) {
            printf("\nOne of the solutions: ");
            solution_chromosome = chromosome;
            print_chromosome(solution_chromosome, *current_fitness);
            break;
        }
        current_fitness++;
    }

    vector<vector<char>> board(
        nq,
        vector<char>(nq, 'x')
    );

    for (int i = 0; i < nq; ++i) {
        board[nq - solution_chromosome[i].row][i] = 'Q';
    }

    for(auto row : board)
    {
        for (auto col : row) {
            printf("%c ", col);
        }
        printf ("\n");
    }
}
