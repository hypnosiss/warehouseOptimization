#pragma once
#include <ctime>
#include <string>

enum PrintSeverity {High, Medium, Low};

class Helpers
{
    public:
        static int getRandNumber(unsigned int from, unsigned int to);
        static void print(PrintSeverity ps, const char *fmt, ...);

    class StopWatch
    {
        public:
            StopWatch(std::string name);
            StopWatch(PrintSeverity ps, std::string name); 
            ~StopWatch();
        private:
            std::clock_t start;
            std::string name;
            PrintSeverity ps;
            bool isPs;
    };
};
