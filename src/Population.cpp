#include "Population.hpp"
#include "Configuration.hpp"
#include "Helpers.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>

void Population::selection(SelectionOperator *selection)
{
    selection->perform(population);
}

void Population::crossing()
{
    unsigned int sizeOfPopulation = population.size();
    unsigned int numberOfOffsprings = config.amountOfPopulation - sizeOfPopulation;
    for (unsigned int i=0; i < numberOfOffsprings; i++)
    {
        int firstParentId, secondParentId;
        do {
            firstParentId = Helpers::getRandNumber(0, sizeOfPopulation-1);
            secondParentId = Helpers::getRandNumber(0, sizeOfPopulation-1);
        } while (firstParentId == secondParentId);

        unsigned int breakPoint = config.amountOfTypesOfProducts/2;
        Individual ind;
        const Individual & firstParent = population[firstParentId];
        const Individual & secondParent = population[secondParentId];

        for (unsigned int j=0; j < breakPoint; j++)
        {
            if (!firstParent.isItemExists(j)) continue;

            unsigned int productId = firstParent[j].productId;
            ind.addItem(productId, firstParent[j]);
        }
        
        for (unsigned int j=breakPoint; j < config.amountOfTypesOfProducts; j++)
        {
            if (!secondParent.isItemExists(j)) continue;

            unsigned int productId = secondParent[j].productId;
            ind.addItem(productId, secondParent[j]);
        }
        population.push_back(ind);
    }

    if (population.size() != config.amountOfPopulation)
        throw std::string("Wrong population size after crossing");
}

void Population::mutation()
{
    unsigned int numberOfIndividuals = config.amountOfPopulation * config.proportionInMutation;
    Helpers::print(Medium, "%u individuals are having mutation", numberOfIndividuals);
    for (unsigned int i=0; i < numberOfIndividuals; i++)
    {
        unsigned int indNr = static_cast<unsigned int>(Helpers::getRandNumber(0, config.amountOfPopulation-1));
        Individual & ind = population[indNr];
        unsigned int productId;
        do
        {
            productId = static_cast<unsigned int>(Helpers::getRandNumber(0, config.amountOfTypesOfProducts-1));
        } while (!ind.isItemExists(productId));

        int amount = Helpers::getRandNumber(1, config.maxPiecesPerItem);
        ind[productId].amount = amount;
    }
}

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

            int amount = Helpers::getRandNumber(1, config.maxPiecesPerItem);
            individual.addItem(productId, Item{.productId=productId, .amount=amount});
        }
        population.push_back(individual);
    }      
}

const Individual & Population::getTheBestResult()
{
    auto ind = std::max_element(population.begin(), population.end(),
                [](const Individual &a, const Individual & b){ return a.getFitnessValue() < b.getFitnessValue(); });

    return *ind;
}

unsigned int Population::calculateFitnessFunctions(const Requests & requests, const Products & products)
{
    unsigned int total = 0;
    for (Individual & ind: population)
    {
        int value = ind.calculateFitnessFunction(requests, products);
        if (value < 0)
            throw std::string("Fitness function cannot be negative. Probably the configuration is wrong");
        total += static_cast<unsigned int>(value);
    }
    return total;
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



