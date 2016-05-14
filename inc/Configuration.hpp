#pragma once
#include <string>

extern struct Configuration
{
    //Population
    unsigned int maxPiecesPerItem, minItemsInIndividual, maxItemsInIndividual, amountOfPopulation;
    
    //Products
    unsigned int amountOfTypesOfProducts, maxWeightOfItem;

    //Requests
    unsigned int maxPiecesPerItemInRequest, amountOfRequests, maxItemsInRequest;
    unsigned int minItemsInRequest;
    
    //Algorithm
    int penalty;
    float proportionInSelection;
    float proportionInMutation;
    float proportionForElite;
    unsigned int numberOfForecasts;
    unsigned int numberOfGenerations;
    unsigned int iterationsOfNoImprove;
    unsigned int amountOfGroupsInTournament;

    void load();
    void saveToFile(std::string fileName);
    void loadFromFile(std::string fileName);
} config;


