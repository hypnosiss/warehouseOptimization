#pragma once
#include <vector>
#include "Individual.hpp"

class Population
{
    public:
        Population();
        int generatePopulation(unsigned int amount);
    protected:
        int test;
        std::vector < Individual > population;
};
