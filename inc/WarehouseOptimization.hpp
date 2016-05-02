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
        unsigned int calculateFitness(const Requests & _requests);
        Requests createGroupOfRequests(unsigned int from, unsigned int to);
        void selection(SelectionMethod sm);
        void crossing();
        void mutation();

        void loadData();
        unsigned int calcDeliveryFrequency();
        void showProgress(unsigned int i);
};
