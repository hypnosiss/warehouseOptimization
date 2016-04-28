#include "RouletteOperator.hpp"
#include "Configuration.hpp"
#include "Helpers.hpp"
#include <string>
#include <algorithm>
#include <iostream>


RouletteOperator::RouletteOperator(): average(0)
{
 
}

void RouletteOperator::perform(std::vector < Individual > &pop)
{
    population = &pop;
    std::vector < Individual > newPopulation(config.amountOfPopulation);
    for_each(population->begin(), population->end(), 
            [this](const Individual &ind) { average += ind.getFitnessValue(); });

    for (unsigned int i=0; i < config.amountOfPopulation; i++)
    {
        const Individual & ind = pickUpNewIndividual();
        newPopulation.push_back(ind);
    }
    population->clear();
    *population = newPopulation;
}

const Individual & RouletteOperator::pickUpNewIndividual()
{
    int fitness = Helpers::getRandNumber(0, average);  
    for (const Individual & individual : *population)
    {
        int individualFitness = individual.getFitnessValue();
        if (individualFitness < 0)
            throw std::string("Size of field cannot be negative");
        fitness -= individualFitness;
        if (fitness <= 0)
        {
#if DEBUG==1
            std::cout << "Individual with fitness " << individual.getFitnessValue() << " has been choosen" << std::endl;
#endif
            return individual;
        }
    }
    throw std::string("Something goes wrong");
}
