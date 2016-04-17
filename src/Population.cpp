#include "Population.hpp"
#include "Configuration.hpp"
#include "Helpers.hpp"
#include <string>
#include <iostream>

void Population::generatePopulation(unsigned int amountOfPopulation)
{
    if (0 == amountOfPopulation)
        throw std::string("The population cannot consist of zero individuals");

    population.clear();
    for(unsigned int i=0; i < amountOfPopulation; i++)
    {
        unsigned int productId = static_cast<unsigned int>(Helpers::getRandNumber(0, config.maxTypesOfProducts));
        unsigned int amount = static_cast<unsigned int>(Helpers::getRandNumber(0, config.maxPiecesPerItem));
        population.push_back(Individual{.productId=productId, .amount=amount});
        std::cout << "productId=" << population.back().productId << std::endl;
    }      
}

