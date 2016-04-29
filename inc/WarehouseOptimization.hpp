#pragma once
#include "Population.hpp"
#include "Products.hpp"
#include "Requests.hpp"
#include "Helpers.hpp"

enum SelectionMethod { ROULETTE, TOURNAMENT };

class WarehouseOptimization
{
    public:
        WarehouseOptimization();
        void perform(); 
    private:
        Population population;
        Requests requests;

        Products products;
        void selection(SelectionMethod sm);
        void crossing();
        void mutation();
};
