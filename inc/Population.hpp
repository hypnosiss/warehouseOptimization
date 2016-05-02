#pragma once
#include <vector>
#include <string>
#include "Individual.hpp"
#include "SelectionOperator.hpp"

class Population
{
    public:
        void generate();
        unsigned int calculateFitnessFunctions(const Requests & requests, const Products & products);
        const Individual & getTheBestResult();
        void loadFromFile(std::string fileName);
        void saveToFile(std::string fileName);
        
        void selection(SelectionOperator *selection);
        void crossing();
        void mutation();
    protected:
        std::vector < Individual > population;
};
