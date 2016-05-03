#include "WarehouseOptimization.hpp"
#include "Configuration.hpp"
#include "Helpers.hpp"
#include "RouletteOperator.hpp"
#include <iostream>

WarehouseOptimization::WarehouseOptimization()
{
    srand(time(NULL));  
}

void WarehouseOptimization::loadData()
{
        products.generate();
     //   products.loadFromFile("products_database.txt");
        products.saveToFile("products_database.txt");
        requests.generate();
       // requests.loadFromFile("requests_database.txt");
        requests.saveToFile("requests_database.txt");
        population.generate();
       // population.loadFromFile("population_database.txt");
        population.saveToFile("population_database.txt");
}

void WarehouseOptimization::perform()
{
    try{
        loadData();
        Helpers::StopWatch sw(High, "PERFORM");
        unsigned int supplyFrequency = calcDeliveryFrequency();
        unsigned int nmbOfIterInGroup=1;
        unsigned int numberOfDelivery=0;
        unsigned int requestsFromId=0;
        unsigned int requestsToId=supplyFrequency-1;

        Helpers::print(Medium, "Total amount of requests = %u", requests.getSize());
        while (numberOfDelivery <= config.numberOfDeliveries)//(requestsToId < config.amountOfRequests )
        {
            Helpers::print(Medium, "-> %u iteration in group, after %u delivery", nmbOfIterInGroup,  numberOfDelivery);
            Requests groupOfRequests = createGroupOfRequests(requestsFromId, requestsToId);

            Helpers::print(Medium, "Group <%u, %u> (%u elements)", requestsFromId, requestsToId, groupOfRequests.getSize());
            
            int numberOfIterations = config.numberOfIterations - groupOfRequests.getSize();
            
            if (numberOfIterations <= 0)
                throw std::string("Too less number of iterations in configuration file!");

            unsigned int previousFitnessFunction=-1;
            unsigned int sameFitnessCount=0;
            
            for (unsigned int i=0; i < (unsigned int)numberOfIterations && sameFitnessCount < config.iterationsOfNoImprove; i++)
            {
                Helpers::print(Low, "Sub-iteration %u/%u", i+1, config.numberOfIterations);
               
                unsigned int fitnessFunction = calculateFitness(groupOfRequests);
                sameFitnessCount = (fitnessFunction > previousFitnessFunction) ? 0 : sameFitnessCount+1;
                if (sameFitnessCount == config.iterationsOfNoImprove-1)
                    Helpers::print(High, "WRN: Did not find improve of fitness function since %u iterations", sameFitnessCount+1);
                previousFitnessFunction = fitnessFunction;

                selection(ROULETTE);
                crossing();
                mutation();
            }
            
            requestsFromId = supplyFrequency*(numberOfDelivery);
            requestsToId = supplyFrequency*(numberOfDelivery+1) - 1;

            if (supplyFrequency == nmbOfIterInGroup)
            {
                nmbOfIterInGroup=1;
                numberOfDelivery++;
                if (numberOfDelivery <= config.numberOfDeliveries)
                    showProgress(numberOfDelivery);
            }
            else
                nmbOfIterInGroup++;
            
        }
    } catch (std::string e)
    {
        std::cerr << "=== ! " << e << " ! ===" << std::endl;
    }
    const Individual &ind = population.getTheBestResult();
    Helpers::print(High, "The best individual with %u ", ind.getFitnessValue());
    saveResults("results.csv");
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

unsigned int WarehouseOptimization::calcDeliveryFrequency()
{
    unsigned int freq = static_cast<unsigned int>(config.amountOfRequests/config.numberOfDeliveries);

    Helpers::print(Low, "Supply frequency = %u", freq);
    return freq;
}

void WarehouseOptimization::addCheckPoint(unsigned int a, unsigned int fitness)
{
    Helpers::print(High, "Check point nr %u added", a);
    results+=std::to_string(a) + std::string(", ") + std::to_string(fitness) +std::string("\n");   
}

void WarehouseOptimization::saveResults(std::string name)
{
    std::ofstream file(name);
    file << results << std::endl;
    file.close();
}

void WarehouseOptimization::showProgress(unsigned int i)
{
    unsigned int max = config.numberOfDeliveries;
    unsigned int distanceToShow = max/config.numberOfStatusInfos;
    const Individual &ind = population.getTheBestResult();
    addCheckPoint(i, ind.getFitnessValue());
    if (i%distanceToShow == distanceToShow-1)
    {
         Helpers::print(High, "Progress (info %u/%u)", i/distanceToShow+1, config.numberOfStatusInfos);
         Helpers::print(High, "The best individual = %u ", ind.getFitnessValue());
    }
}
