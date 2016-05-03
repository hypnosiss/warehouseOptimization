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
    
    //Algorithm
    int penalty;
    float proportionInSelection;
    float proportionInMutation;
    unsigned int numberOfDeliveries;
    unsigned int numberOfIterations;
    unsigned int iterationsOfNoImprove;
    unsigned int numberOfStatusInfos;
    void loadConfiguration();
} config;


