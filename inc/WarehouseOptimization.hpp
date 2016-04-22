#pragma once
#include "Population.hpp"
#include "Product.hpp"
#include "Requests.hpp"
#include "Helpers.hpp"
//todo: add load and save from file requests + same for products
class WarehouseOptimization
{
    public:
        void generateProducts(); 
    private:
        Population population;
        Requests requests;

        Products products;
};
