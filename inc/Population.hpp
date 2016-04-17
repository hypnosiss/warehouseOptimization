#pragma once
#include <vector>
#include "Individual.hpp"
class Population
{
    public:
        void generatePopulation(unsigned int amount);
    protected:
        std::vector < Individual > population;
};
