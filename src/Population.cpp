#include "Population.hpp"
#include "Configuration.hpp"
#include "Helpers.hpp"
#include <iostream>
#include <fstream>

void Population::generate(unsigned int amountOfPopulation)
{
    if (0 == amountOfPopulation)
        throw std::string("The population cannot consist of zero individuals");

    population.clear();
    for(unsigned int i=0; i < amountOfPopulation; i++)
    {
        unsigned int amountOfItems = static_cast<unsigned int>(Helpers::getRandNumber(0, config.maxItems));
        Individual individual;
        for (unsigned int j=0; j < amountOfItems; j++)
        {
            unsigned int productId;
            do productId = static_cast<unsigned int>(Helpers::getRandNumber(0, config.maxTypesOfProducts));
            while (!individual.isItemExists(productId));

            int amount = Helpers::getRandNumber(0, config.maxPiecesPerItem);
            individual.addItem(productId, Item{.productId=productId, .amount=amount});
        }
        population.push_back(individual);
    }      
}

void Population::saveToFile(std::string fileName)
{
    std::fstream file(fileName);
    file << population.size() << std::endl;
    for(const Individual & ind : population)
    {
        file << ind.getSize() << " ";
        for (unsigned int i=0; i<ind.getSize(); i++)
        {
            Item item = ind[i];
            file << item.productId << " " << item.amount << " ";
        }
        file << std::endl;
    }
}

void Population::loadFromFile(std::string fileName)
{
    std::fstream file(fileName);

    population.clear();
    unsigned int amountOfPopulation;
    file >> amountOfPopulation;
    for (unsigned int i=0; i<amountOfPopulation; i++)
    {
        unsigned int numberOfItems;
        file >> numberOfItems;
        Individual ind;
        for (unsigned int j=0; j<numberOfItems; j++)
        {
            Item item;
            file >> item.productId;
            file >> item.amount;
            ind.addItem(item.productId, item);
        }
        population.push_back(ind);
    }
}



