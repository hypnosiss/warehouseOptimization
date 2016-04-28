#pragma once
#include "Population.hpp"

class SelectionOperator
{
    public:
        virtual void perform(std::vector < Individual > &pop) = 0;
        virtual ~SelectionOperator() { }
};
