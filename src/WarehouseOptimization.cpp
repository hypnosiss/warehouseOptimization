#include "WarehouseOptimization.hpp"
#include "Configuration.hpp"
#include "Helpers.hpp"
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
    } catch (std::string e)
    {
        std::cout << e << std::endl;
    }
}
