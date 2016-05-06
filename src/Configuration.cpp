#include "Configuration.hpp"
#include <string>

Configuration config;

void Configuration::load()
{
    //Population
    amountOfPopulation = 100; // Ilosc osobnikow
    maxItemsInIndividual = 199; // Max ilosc typow produktow u osobnika
    minItemsInIndividual = 100; // Min ilosc typow produktow u osobnika
    maxPiecesPerItem = 20; // Max liczba sztuk danego produktu u osobnika

    //Products
    amountOfTypesOfProducts = 200; // Ilosc typow produktow
    maxWeightOfItem = 100; // Max waga produktu

    //Requests
    amountOfRequests = 100; // Ilosc zadan
    maxItemsInRequest = 20; // Max typow produktow w zadaniu
    minItemsInRequest = 1; // Min typow produktow w zadaniu
    //config.maxTypesOfProducts = 
    maxPiecesPerItemInRequest = 50; // Max liczba sztuk daneg produktu w zadaniu
    
    //Algorithm
    penalty = 2; // kara
    proportionInSelection = 0.40; // Procent osobnikow produkowanych z selekcji
    proportionInMutation = 0.02; // Procent osobnikow produkowanych z mutacji
    proportionForElite = 0.15; // Procent najlepszych osobnikow przechodzacych do pokolenia
    numberOfForecasts = 100; // Ilosc prognoz
    numberOfGenerations = 50; // Ilosc generacji dla danego zestawu zadan (jednej prognozy)
    iterationsOfNoImprove = 25; // Warunek stopu jesli nie ma poprawy w zestawie zadan

    //Debug
    numberOfStatusInfos = 10; // Ile komunikatow ma byc wyswietlonych

    if (maxItemsInIndividual >= amountOfTypesOfProducts)
        throw std::string("MaxItemsInIndividual cannot be higher than number of products");

    if (static_cast<unsigned int>(amountOfRequests/numberOfForecasts) == 0)
        throw std::string("Too big number of forecasts");
}
