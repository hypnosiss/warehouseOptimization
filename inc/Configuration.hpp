#pragma once

extern struct Configuration
{
    unsigned int maxPiecesPerItem, maxItems, maxTypesOfProducts, maxWeightOfItem;
    void loadConfiguration();
} config;

