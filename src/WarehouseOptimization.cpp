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
        Helpers::StopWatch measuring(High, "PERFORM");
        unsigned int supplyFrequency = calcDeliveryFrequency();
        unsigned int numberOfDelivery=0;
        unsigned int requestsFromId=0;
        unsigned int requestsToId=supplyFrequency-1;

        Helpers::print(Medium, "Total amount of requests = %u", requests.getSize());
        while (numberOfDelivery <= config.numberOfDeliveries)//(requestsToId < config.amountOfRequests )
        {
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
                
                generationChart(i);
            }
            
            requestsFromId = supplyFrequency*(numberOfDelivery);
            requestsToId = supplyFrequency*(numberOfDelivery+1) - 1;

            numberOfDelivery++;
            if (numberOfDelivery <= config.numberOfDeliveries)
                showProgress(numberOfDelivery);
            
        }
    } catch (std::string e)
    {
        std::cerr << "=== ! " << e << " ! ===" << std::endl;
    }
    unsigned int min,max,average;
    population.getStatistics(min, average,max);
    Helpers::print(High, "Results: The worst:%u, average:%u, The best:%u ", min, average, max);
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

void WarehouseOptimization::generationChart(unsigned int i)
{
    unsigned int min,max,average;
    population.getStatistics(min, average,max);
    if (i < fitnessPerGeneration.size())
        fitnessPerGeneration[i] +=  max;
    else
        fitnessPerGeneration.push_back(max);
}

void WarehouseOptimization::addCheckPoint(unsigned int a)
{
    unsigned int min,max,average;
    population.getStatistics(min, average,max);

    Helpers::print(High, "Check point nr %u added", a);
    results+=std::to_string(a) + std::string(", ") + 
             std::to_string(min) + std::string(", ") +
             std::to_string(average) + std::string(", ") +
             std::to_string(max) + std::string("\n");   
}

void WarehouseOptimization::saveResults(std::string name)
{
    std::string nameDeliveries = std::string("D_") + name;
    std::ofstream file1(nameDeliveries);
    file1 << results << std::endl;
    file1.close();

    std::string nameGenerations = std::string("G_") + name;
    std::ofstream file2(nameGenerations);
    for (unsigned int i=0; i < fitnessPerGeneration.size(); i++)
    {
        file2 << std::to_string(i) + std::string(", ") + 
                std::to_string(fitnessPerGeneration[i]) + std::string("\n");
    }
    file2.close();
}


void WarehouseOptimization::showProgress(unsigned int i)
{
    unsigned int max = config.numberOfDeliveries;
    unsigned int distanceToShow = max/config.numberOfStatusInfos;

    addCheckPoint(i);
    if (i%distanceToShow == distanceToShow-1)
    {
         Helpers::print(High, "Progress (info %u/%u)", i/distanceToShow+1, config.numberOfStatusInfos);
    }
}
