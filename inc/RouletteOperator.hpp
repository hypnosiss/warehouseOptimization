#pragma once
#include "Population.hpp"
#include "SelectionOperator.hpp"
#include <vector>

class RouletteOperator : public SelectionOperator
{
    public:
        RouletteOperator();
        virtual void perform(std::vector < Individual > &pop);

    private:
        std::vector < Individual > * population;
        int total;
        const Individual & pickUpNewIndividual();
};
