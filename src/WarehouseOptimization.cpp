#include "WarehouseOptimization.hpp"
#include "Configuration.hpp"
#include "Helpers.hpp"
#include "RouletteOperator.hpp"
#include "TournamentOperator.hpp"
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

void WarehouseOptimization::createGeneration()
{
    selection(TOURNAMENT);
    crossing();
    mutation();
}

void WarehouseOptimization::createGenerations(Requests & groupOfRequests)
{
    unsigned int previousFitness=0;
    unsigned int biggerFitnessCounter=0;
    for (unsigned int i=0; i < config.numberOfGenerations && 
                           biggerFitnessCounter < config.iterationsOfNoImprove; i++)
    {
       
        unsigned int currentFitness = calculateFitness(groupOfRequests);
        biggerFitnessCounter = (currentFitness > previousFitness) ? 0 : biggerFitnessCounter+1;
        if (biggerFitnessCounter == config.iterationsOfNoImprove-1)
        {
            Helpers::print(High, "WRN: Did not find improve of fitness value "
                                 "since %u iterations", 
                           biggerFitnessCounter+1);
            break;
        }
        previousFitness = currentFitness;
        
        Helpers::print(Low, "Generation %u/%u", i+1, config.numberOfGenerations);
        createGeneration();
        
        addRowToGenerationTypeData(i);
    }

}

void WarehouseOptimization::perform()
{
    Helpers::StopWatch measuring(High, "PERFORM");
    unsigned int forecastFrequency = calculateFrequencyOfForecastsForRequests();
    unsigned int numberOfForecast=0;
    unsigned int requestsFromId=0;
    unsigned int requestsToId=forecastFrequency-1;

    Helpers::print(Low, "Total amount of requests = %u", requests.getSize());

    while (numberOfForecast <= config.numberOfForecasts)
    {
        Requests groupOfRequests = createGroupOfRequests(requestsFromId, requestsToId);

        Helpers::print(High, "Forecast no.%u -> basing on group of "
                             "<%u, %u> requests (%u elements)", 
                       numberOfForecast, requestsFromId, requestsToId, 
                       groupOfRequests.getSize());
        
        createGenerations(groupOfRequests); 

        requestsFromId = forecastFrequency*(numberOfForecast);
        requestsToId = forecastFrequency*(numberOfForecast+1) - 1;

        numberOfForecast++;

        addRowToForecastTypeData();
       // if (numberOfForecast <= config.numberOfForecasts)
    }
    printStatistics();    
    saveResults("results.csv");
}

void WarehouseOptimization::printStatistics()
{
    unsigned int min,max,average;
    population.getStatistics(min, average, max);
    Helpers::print(High, "The worst: %u, average: %u, the best: %u ", min, average, max);
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
    unsigned int total = population.calculateFitnessValues(_requests, products);
    Helpers::print(Low, "Total fitness function in current population = %u", total);
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
    case TOURNAMENT:
        selectionOperator = new TournamentOperator();
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

unsigned int WarehouseOptimization::calculateFrequencyOfForecastsForRequests()
{
    unsigned int f = static_cast<unsigned int>(config.amountOfRequests/config.numberOfForecasts);
    Helpers::print(Low, "Frequency of forecasts for all requests is %u", f);
    return f;
}

void WarehouseOptimization::addRowToGenerationTypeData(unsigned int generationId)
{
    unsigned int min,max,average;
    population.getStatistics(min, average,max);

    if (generationId < fitnessPerGeneration.size())
        fitnessPerGeneration[generationId] +=  max;
    else
        fitnessPerGeneration.push_back(max);
}

void WarehouseOptimization::addRowToForecastTypeData()
{
    unsigned int min,max,average;
    population.getStatistics(min, average,max);

    forecastResults+= std::to_string(min) + std::string(", ") +
              std::to_string(average) + std::string(", ") +
              std::to_string(max) + std::string("\n");   
    Helpers::print(Low, "Checkpoint for forecast data has been added");
}

void WarehouseOptimization::saveResults(std::string name)
{
    std::string nameForForecasts = std::string("F_") + name;
    std::ofstream fFile(nameForForecasts);
    fFile << forecastResults << std::endl;
    fFile.close();

    std::string nameForGenerations = std::string("G_") + name;
    std::ofstream gFile(nameForGenerations);
    for (unsigned int i=0; i < fitnessPerGeneration.size(); i++)
    {
        gFile << std::to_string(fitnessPerGeneration[i]) + std::string("\n");
    }
    gFile.close();
}
