#include "Population.hpp"
#include "Configuration.hpp"
#include "Helpers.hpp"
#include <iostream>
Population::Population()
{
    
}

int Population::generatePopulation(unsigned int amountOfPopulation)
{
    for(unsigned int i=0; i < amountOfPopulation; i++)
    {
        unsigned int productId = static_cast<unsigned int>(getRandNumber(0, config.maxTypesOfProducts));
        unsigned int amount = static_cast<unsigned int>(getRandNumber(0, config.maxPiecesPerItem));
        population.push_back(Individual{.productId=productId, .amount=amount});
    }      
    return 2;
}
