#pragma once
#include <vector>
#include <string>
#include "Individual.hpp"

class Population
{
    public:
        void generate(unsigned int amount);
        void loadFromFile(std::string fileName);
        void saveToFile(std::string fileName);
    protected:
        std::vector < Individual > population;
};
