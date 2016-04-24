#pragma once

extern struct Configuration
{
    //Population
    unsigned int maxPiecesPerItem, minItemsInIndividual, maxItemsInIndividual, amountOfPopulation;
    
    //Products
    unsigned int amountOfTypesOfProducts, maxWeightOfItem;

    //Requests
    unsigned int maxPiecesPerItemInRequest, amountOfRequests, maxItemsInRequest;
    unsigned int minItemsInRequest;
    int penalty;
    void loadConfiguration();
} config;

