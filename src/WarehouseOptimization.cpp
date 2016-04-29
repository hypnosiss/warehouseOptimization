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

        for (unsigned int i=0; i < 5; i++)
        {
            selection(ROULETTE);
            crossing();
            mutation();
        }
    } catch (std::string e)
    {
        std::cout << e << std::endl;
    }
}

void WarehouseOptimization::selection(SelectionMethod sm)
{
    population.calculateFitnessFunctions(requests, products);
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

}
