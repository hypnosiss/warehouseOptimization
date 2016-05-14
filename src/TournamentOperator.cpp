#include "TournamentOperator.hpp"
#include "Configuration.hpp"
#include "Helpers.hpp"
#include <string>
#include <algorithm>
#include <iostream>


TournamentOperator::TournamentOperator()
{
 
}

void TournamentOperator::perform(std::vector < Individual > &pop)
{
    population = &pop;//poprawic reserve
    std::vector < Individual > newPopulation;
    
    unsigned int sizeOfNewPopulation = config.amountOfPopulation*config.proportionInSelection;
    unsigned int sizeOfGroup = sizeOfNewPopulation / config.amountOfGroupsInTournament;
    
    for (unsigned int i=0; i < sizeOfNewPopulation; i++)
    {
        const Individual ind = pickUpNewIndividual(sizeOfGroup);
        newPopulation.push_back(ind);
    }
    population->clear();
    *population = newPopulation;
}

const Individual TournamentOperator::pickUpNewIndividual(unsigned int sizeOfGroup)
{
    std::vector < Individual > group;
    for (unsigned int i=0; i < sizeOfGroup; i++)
    {
        int individualId = Helpers::getRandNumber(0, population->size()-1);
        group.push_back(population->at(individualId));
    }

    std::sort( group.begin( ), group.end( ), [ ]( const Individual& lhs, const Individual& rhs )
    {
        return lhs.getFitnessValue() > rhs.getFitnessValue();
    });
    
    return group.front();
}
