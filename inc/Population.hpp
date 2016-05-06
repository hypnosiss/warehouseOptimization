#pragma once
#include <vector>
#include <string>
#include "Individual.hpp"
#include "SelectionOperator.hpp"

class Population
{
    public:
        void generate();
        void getStatistics(unsigned int &min, unsigned int &average, unsigned int &max);
        unsigned int calculateFitnessValues(const Requests & requests, const Products & products);
        void loadFromFile(std::string fileName);
        void saveToFile(std::string fileName);
        
        void selection(SelectionOperator *selection);
        void crossing();
        void mutation();
    protected:
        std::vector < Individual > population;
        std::vector <Individual> pickUpElite();
        void sort();
};
