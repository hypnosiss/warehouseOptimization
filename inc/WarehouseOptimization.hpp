#pragma once
#include "Population.hpp"
#include "Product.hpp"
#include "Helpers.hpp"

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
