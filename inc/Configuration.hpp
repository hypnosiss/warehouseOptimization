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
    unsigned int individualsInGroup;
    float proportionInSelection;
    float proportionInMutation;
    unsigned int numberOfDeliveries;
    unsigned int numberOfIterations;

    void loadConfiguration();
} config;

#define DEBUG 1

