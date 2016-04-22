#pragma once

extern struct Configuration
{
    unsigned int maxPiecesPerItem, maxItems, maxTypesOfProducts, maxWeightOfItem, amountOfRequests;

    unsigned int maxPiecesPerItemInRequest, maxItemsInRequest;
    int penalty;
    void loadConfiguration();
} config;

