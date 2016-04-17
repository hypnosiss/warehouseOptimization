#include <ctime>
#include <cstdlib>
#include <string>
#include "Helpers.hpp"

int Helpers::getRandNumber(unsigned int from, unsigned int to)
{
    if (0 == to)
        throw std::string("You cannot divide by zero");
    srand(time(NULL));  
    return (rand()%to + from); 
}

