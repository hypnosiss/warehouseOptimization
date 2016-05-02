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

        Helpers::StopWatch sw("PERFORM");
        unsigned int supplyFrequency = static_cast<unsigned int>(config.amountOfRequests/config.numberOfDeliveries);
      //  std::cout << "Supply frequency = " << supplyFrequency << std::endl;
        Helpers::print(Medium, "Supply frequency = %u", supplyFrequency);
        unsigned int nmbOfIterInGroup=1;
        unsigned int numberOfDelivery=0;
        unsigned int requestsFromId=0;
        unsigned int requestsToId=0;


        Helpers::print(Medium, "Total amount of requests = %u", requests.getSize());
        while (requestsToId < config.amountOfRequests )
        {
            Helpers::print(Low, "-> %u iteration in group, after %u delivery", nmbOfIterInGroup,  numberOfDelivery);
            requestsFromId = supplyFrequency*(numberOfDelivery);
            requestsToId = supplyFrequency*(numberOfDelivery+1) - 1;
            Requests groupOfRequests = createGroupOfRequests(requestsFromId, requestsToId);
            Helpers::print(Low, "Group <%u, %u> (%u elements)", requestsFromId, requestsToId, groupOfRequests.getSize());
            
            unsigned int previousFitnessFunction=-1;
            unsigned int sameFitnessCount=0;
            
            for (unsigned int i=0; i < config.numberOfIterations && sameFitnessCount < config.iterationsOfNoImprove; i++)
            {
                Helpers::print(Low, "Sub-interation %u/%u", i+1, config.numberOfIterations);
               
                unsigned int fitnessFunction = calculateFitness(groupOfRequests);
                sameFitnessCount = (fitnessFunction != previousFitnessFunction) ? 0 : sameFitnessCount+1;
                if (sameFitnessCount == config.iterationsOfNoImprove-1)
                    Helpers::print(High, "Did not find improve of fitness function since %u iterations", sameFitnessCount+1);
                previousFitnessFunction = fitnessFunction;

                selection(ROULETTE);
                crossing();
                mutation();
            }

            if (supplyFrequency == nmbOfIterInGroup)
            {
                nmbOfIterInGroup=1;
                numberOfDelivery++;
            }
            else
                nmbOfIterInGroup++;
        }
    } catch (std::string e)
    {
        std::cerr << "=== ! " << e << " ! ===" << std::endl;
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

unsigned int WarehouseOptimization::calculateFitness(const Requests & _requests)
{
    Helpers::StopWatch measuring("CALCULATE FITNESS FUNCTION");
    unsigned int total = population.calculateFitnessFunctions(_requests, products);
    Helpers::print(Medium, "Total fitness function in current population = %u", total);
    return total;
}

void WarehouseOptimization::selection(SelectionMethod sm)
{
    Helpers::StopWatch measuring("SELECTION");
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
    Helpers::StopWatch measuring("CROSSING");
    population.crossing();       
}

void WarehouseOptimization::mutation()
{
    Helpers::StopWatch measuring("MUTATION");
    population.mutation();
}
