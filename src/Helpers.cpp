#include <ctime>
#include <cstdlib>
#include <string>
#include "Helpers.hpp"

int Helpers::getRandNumber(unsigned int from, unsigned int to)
{
    if (from == to)
        return to;
    if (0 == to)
        throw std::string("You cannot divide by zero");
    return (rand()%(to-from) + from); 
}

