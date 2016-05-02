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
    unsigned int iterationsOfNoImprove;
    void loadConfiguration();
} config;

#define DEBUG 1
/* 3 - Only High
 * 2 - High and Medium
 * 1 - High, Medium and Low */

