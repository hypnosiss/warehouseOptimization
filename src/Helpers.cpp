#include <ctime>
#include <cstdlib>
#include "Configuration.hpp"
#include "Helpers.hpp"
#include <iostream>
#include <string>
#include <cstdarg>

int Helpers::getRandNumber(unsigned int from, unsigned int to)
{
    if (from == to)
        return to;
    if (0 == to)
        throw std::string("You cannot divide by zero");
    return (rand()%(to-from) + from); 
}

void Helpers::print(PrintSeverity ps, const char *fmt, ...)
{
    char buffer[120];
    int length;

    va_list args;

    /* Initialise the va_list variable with the ... after fmt */

    va_start(args, fmt);
   
    length = vsnprintf(buffer, 120, fmt, args);

    if (length >= 120)
        buffer[119] = 0;
    switch (ps)
    {
        case High:
#if DEBUG>0
        printf("%s\n", buffer);
#endif
            break;
        case Medium:
#if DEBUG<3
        printf("%s\n", buffer);
#endif
            break;
        case Low:
#if DEBUG==1
        printf("%s\n", buffer);
#endif
            break;
    }
    
    /* Clean up the va_list */
    va_end(args);
}

Helpers::StopWatch::StopWatch(std::string name):start(std::clock()), name(name)
{
    std::cout << "+++ " << name << " +++" << std::endl; 
}

Helpers::StopWatch::~StopWatch()
{
    clock_t total = clock()-start; //get elapsed time
    std::cout<<"--- "<< name << "(" << double(total)/CLOCKS_PER_SEC<< "secs) ---" << std::endl;
}
