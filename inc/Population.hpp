#pragma once
#include <vector>
#include <string>
#include "Individual.hpp"

class Population
{
    public:
        void generate();
        void calculateFitnessFunctions(const Requests & requests, const Products & products);
        void loadFromFile(std::string fileName);
        void saveToFile(std::string fileName);
    protected:
        std::vector < Individual > population;
};
