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
    config.amountOfPopulation = 100; // Ilosc osobnikow
    config.maxItemsInIndividual = 199; // Max ilosc typow produktow u osobnika
    config.minItemsInIndividual = 100; // Min ilosc typow produktow u osobnika
    config.maxPiecesPerItem = 20; // Max liczba sztuk danego produktu u osobnika

    //Products
    config.amountOfTypesOfProducts = 200; // Ilosc typow produktow
    config.maxWeightOfItem = 100; // Max waga produktu

    //Requests
    config.amountOfRequests = 600; // Ilosc zadan
    config.maxItemsInRequest = 20; // Max typow produktow w zadaniu
    config.minItemsInRequest = 1; // Min typow produktow w zadaniu
    //config.maxTypesOfProducts = 
    config.maxPiecesPerItemInRequest = 50; // Max liczba sztuk daneg produktu w zadaniu
    
    //Algorithm
    config.penalty = 2; // kara
    config.proportionInSelection = 0.40; // Procent osobnikow produkowanych z selekcji
    config.proportionInMutation = 0.02; // Procent osobnikow produkowanych z mutacji
    config.numberOfDeliveries = 100; // Ilosc dostaw
    config.numberOfIterations = 50; // Ilosc iteracji dla danego zestawu zadan
    config.iterationsOfNoImprove = 25; // Warunek stopu jesli nie ma poprawy w zestawie zadan

    //Debug
    config.numberOfStatusInfos = 10; // Ile komunikatow ma byc wyswietlonych

    if (config.maxItemsInIndividual >= config.amountOfTypesOfProducts)
        throw std::string("MaxItemsInIndividual cannot be higher than number of products");

    if (static_cast<unsigned int>(config.amountOfRequests/config.numberOfDeliveries) == 0)
        throw std::string("Too big number of deliveries");
}

int main()
{
    WarehouseOptimization wo;
    loadConfiguration(); 
    wo.perform();
    cout << "Warehouse Line-up Optimization" << endl; 
    return 0;
}
