#pragma once
#include "Population.hpp"
#include "Products.hpp"
#include "Requests.hpp"
#include "Helpers.hpp"
//todo: add load and save from file requests + same for products
class WarehouseOptimization
{
    public:
        WarehouseOptimization();
        void perform(); 
    private:
        Population population;
        Requests requests;

        Products products;
};
