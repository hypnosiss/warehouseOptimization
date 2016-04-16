#pragma once
#include "Population.hpp"
#include "Product.hpp"

using Products = std::vector < Product >;
using Requests = std::vector < std::vector < Individual > >;

class WarehouseOptimization
{
    public:
        void generateProducts(); 
    private:
        Population population;
        Requests requests;

        Products products;
};
