//
// Created by M Nabil Asykar on 4/1/2021.
//

#pragma once

#include <NQueen/Population.hpp>
#include <NQueen/Chromosome.hpp>

#include <vector>

Chromosome Population::randomPick(
        std::vector<double> &weights)
{
    double weightSum = std::accumulate(weights.cbegin(), weights.cend(), 0.0);

    double r = ( static_cast <double> (rand()) / static_cast <double> (RAND_MAX) ) * static_cast<double>(weightSum);
    double distributed_weights = 0;

    auto chromosome = this->chromosomes.begin();
    auto weight = weights.begin()
    for (; chromosome != this->chromosomes.end() || weight != weights.end();)
    {
        if (r <= distributed_weights + *weight)
        {
            return *chromosome;
        }
        distributed_weights += *weight;

        ++chromosome;
        ++weight;
    }

    assert(false && "Unreachable");
}

