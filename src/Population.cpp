#include "Population.hpp"
#include "Configuration.hpp"
#include "Helpers.hpp"
#include <iostream>
#include <fstream>

void Population::generate()
{
    if (0 == config.amountOfPopulation)
        throw std::string("The population cannot consist of zero individuals");

    population.clear();
    for(unsigned int i=0; i < config.amountOfPopulation; i++)
    {
        unsigned int amountOfItems = static_cast<unsigned int>(Helpers::getRandNumber(config.minItemsInIndividual, config.maxItemsInIndividual));
        Individual individual;
        for (unsigned int j=0; j < amountOfItems; j++)
        {
            unsigned int productId = individual.getRandProductId();

            int amount = Helpers::getRandNumber(0, config.maxPiecesPerItem);
            individual.addItem(productId, Item{.productId=productId, .amount=amount});
        }
        population.push_back(individual);
    }      
}

void Population::calculateFitnessFunctions(const Requests & requests, const Products & products)
{
    for (Individual & ind: population)
    {
        unsigned int value = ind.calculateFitnessFunction(requests, products);
        std::cout << "valueC: " << value << std::endl;
    }
   /*
        unsigned int value = population[0].calculateFitnessFunction(requests, products);
        std::cout << "value: "<< value << std::endl;;

        value = population[1].calculateFitnessFunction(requests, products);
        std::cout << "value2 " << value << std::endl;
   */
    std::cout << std::endl;
}

void Population::saveToFile(std::string fileName)
{
    std::ofstream file(fileName);
    file << population.size() << std::endl;
    for(const Individual & ind : population)
    {
        file << ind;
    }
    file.close();
}

void Population::loadFromFile(std::string fileName)
{
    std::ifstream file(fileName);

    population.clear();
    file >> config.amountOfPopulation;
    for (unsigned int i=0; i<config.amountOfPopulation; i++)
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
    file.close();
}



