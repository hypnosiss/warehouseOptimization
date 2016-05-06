#pragma once
#include "Population.hpp"
#include "Products.hpp"
#include "Requests.hpp"
#include "Helpers.hpp"
#include <string>

enum SelectionMethod { ROULETTE, TOURNAMENT };

class WarehouseOptimization
{
    public:
        WarehouseOptimization();
        void loadData();
        void perform(); 
    private:
        Population population;
        Requests requests;

        Products products;
        std::vector <unsigned int> fitnessPerGeneration;
        unsigned int calculateFitness(const Requests & _requests);
        Requests createGroupOfRequests(unsigned int from, unsigned int to);
        void createGenerations(Requests & groupOfRequests);
        void createGeneration();
        void selection(SelectionMethod sm);
        void crossing();
        void mutation();

        unsigned int calculateFrequencyOfForecastsForRequests();
        void addRowToForecastTypeData();
        void printStatistics();
        void addRowToGenerationTypeData(unsigned int generationId);
        void saveResults(std::string name);
        std::string forecastResults;
};
