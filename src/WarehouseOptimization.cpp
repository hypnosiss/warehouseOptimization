#include "WarehouseOptimization.hpp"
#include "Configuration.hpp"
#include "Helpers.hpp"
#include "RouletteOperator.hpp"
#include <string>
#include <iostream>

WarehouseOptimization::WarehouseOptimization()
{
    srand(time(NULL));  
}

void WarehouseOptimization::perform()
{
    try{
        products.generate();
        products.loadFromFile("products_database.txt");
        requests.generate();
        requests.loadFromFile("requests_database.txt");
        population.generate();
        population.loadFromFile("population_database.txt");

        unsigned int supplyFrequency = static_cast<unsigned int>(config.amountOfRequests/config.numberOfDeliveries);
        std::cout << "Supply frequency = " << supplyFrequency << std::endl;
        unsigned int nmbOfIterInGroup=1;
        unsigned int numberOfDelivery=0;
        unsigned int requestsFromId=0;
        unsigned int requestsToId=0;
        std::cout << "Number of requests " << requests.getSize() << std::endl;
        unsigned int a =0;
        while (requestsToId < config.amountOfRequests)
        {
            std::cout << "Iteration in group: " << nmbOfIterInGroup << ", delivery: " << numberOfDelivery << std::endl;
            requestsFromId = supplyFrequency*(numberOfDelivery);
            requestsToId = supplyFrequency*(numberOfDelivery+1) - 1;
            std::cout << "Group from " << requestsFromId << " to " << requestsToId << std::endl;
            Requests groupOfRequests = createGroupOfRequests(requestsFromId, requestsToId);
            std::cout << "Number of requests in group " << groupOfRequests.getSize() << std::endl;
            calculateFitness(groupOfRequests);
            selection(ROULETTE);
            crossing();
            mutation();

            if (supplyFrequency == nmbOfIterInGroup)
            {
                nmbOfIterInGroup=1;
                numberOfDelivery++;
            }
            else
                nmbOfIterInGroup++;
            a++;
        }
    } catch (std::string e)
    {
        std::cout << e << std::endl;
    }
}

Requests WarehouseOptimization::createGroupOfRequests(unsigned int from, unsigned int to)
{
    Requests newRequests;
    for (unsigned int i=from; i<= to; i++)
    {
        newRequests.addVectorOfItems(requests[i]);
    }
    return newRequests;
}

void WarehouseOptimization::calculateFitness(const Requests & _requests)
{
    population.calculateFitnessFunctions(_requests, products);
}

void WarehouseOptimization::selection(SelectionMethod sm)
{
    SelectionOperator * selectionOperator = NULL;
    switch(sm)
    {
    case ROULETTE:
        selectionOperator = new RouletteOperator();
        break;

    }
    population.selection(selectionOperator);
    delete selectionOperator;
}

void WarehouseOptimization::crossing()
{
    population.crossing();       
}

void WarehouseOptimization::mutation()
{
    population.mutation();
}
