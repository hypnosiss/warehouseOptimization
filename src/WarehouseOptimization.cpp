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
        population.calculateFitnessFunctions(requests, products);

        selection(ROULETTE);
        crossing();
    } catch (std::string e)
    {
        std::cout << e << std::endl;
    }
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
