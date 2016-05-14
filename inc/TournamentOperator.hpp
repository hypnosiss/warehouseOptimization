#pragma once
#include "Population.hpp"
#include "SelectionOperator.hpp"
#include <vector>

class TournamentOperator : public SelectionOperator
{
    public:
        TournamentOperator();
        virtual void perform(std::vector < Individual > &pop);

    private:
        std::vector < Individual > * population;
        const Individual pickUpNewIndividual(unsigned int sizeOfGroup);
};
