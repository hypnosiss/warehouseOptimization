#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Products.hpp"
#include "Individual.hpp"
#include "Configuration.hpp"
#include "WarehouseOptimization.hpp"
using namespace std;

void loadConfiguration()
{
    //Population
    config.amountOfPopulation = 30;
    config.maxItemsInIndividual = 20;
    config.minItemsInIndividual = 5;
    config.maxPiecesPerItem = 20;

    //Products
    config.amountOfTypesOfProducts = 21;
    config.maxWeightOfItem = 10;

    //Requests
    config.amountOfRequests = 5;
    config.maxItemsInRequest = 10;
    config.minItemsInRequest = 6;
    //config.maxTypesOfProducts = 
    config.maxPiecesPerItemInRequest = 5;
    
    //Algorithm
    config.penalty = 2;
    config.individualsInGroup = 7;

    if (config.maxItemsInIndividual >= config.amountOfTypesOfProducts)
        throw std::string("MaxItemsInIndividual cannot be higher than number of products");
}

int main()
{
    WarehouseOptimization wo;
    loadConfiguration(); 
    wo.perform();
    cout << "Warehouse Line-up Optimization" << endl; 
    return 0;
}
