#include "RouletteOperator.hpp"
#include "Configuration.hpp"
#include "Helpers.hpp"
#include <string>
#include <algorithm>
#include <iostream>


RouletteOperator::RouletteOperator(): total(0)
{
 
}

void RouletteOperator::perform(std::vector < Individual > &pop)
{
    population = &pop;
    std::vector < Individual > newPopulation;
    newPopulation.reserve(config.amountOfPopulation);
    for_each(population->begin(), population->end(), 
            [this](const Individual &ind) { if (ind.isActive) total += ind.getFitnessValue(); else throw std::string("Detect non-active individual");});

    std::cout << "Total fitness function in current population = " << total << std::endl;
    
    unsigned int sizeOfNewPopulation = config.amountOfPopulation*config.proportionInSelection;
    for (unsigned int i=0; i < sizeOfNewPopulation ; i++)
    {
        const Individual & ind = pickUpNewIndividual();
        newPopulation.push_back(ind);
        newPopulation.back().isActive = true;
    }
    population->clear();
    *population = newPopulation;
}

const Individual & RouletteOperator::pickUpNewIndividual()
{
    int fitness = Helpers::getRandNumber(0, total);  
    for (Individual & individual : *population)
    {
        if (!individual.isActive) continue;
        int individualFitness = individual.getFitnessValue();
        if (individualFitness < 0)
            throw std::string("Size of field cannot be negative");
        fitness -= individualFitness;
        if (fitness <= 0)
        {
#if DEBUG==1
            std::cout << "Individual with fitness " << individual.getFitnessValue() << " has been choosen" << std::endl;
#endif
            total -= individual.getFitnessValue();
            individual.isActive = false;
            return individual;
        }
    }
    throw std::string("Something goes wrong");
}
