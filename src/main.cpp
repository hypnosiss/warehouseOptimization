#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>
#include "Products.hpp"
#include "Individual.hpp"
#include "Configuration.hpp"
#include "WarehouseOptimization.hpp"
using namespace std;

void generateGroup(unsigned int sizeOfGroup)
{
        config.load();
        config.amountOfRequests = 0;
        for (unsigned int i=0; i < 10; i++)
        {
            config.amountOfRequests += 100;
            config.numberOfForecasts = static_cast<unsigned int>(config.amountOfRequests/sizeOfGroup);
            cout << "Warehouse Line-up Optimization" << endl; 
            cout << "Number of forecasts: " << config.numberOfForecasts << endl;
            cout << "Amount of demands: " << config.amountOfRequests << endl;
            WarehouseOptimization wo;
            string code = to_string(i+1) + string("-") + to_string(config.amountOfRequests) + string("_") + to_string(sizeOfGroup) + string("_") + to_string(config.amountOfPopulation) + string("_");
            wo.setCode(code);
            wo.loadData();
            wo.perform();
        }

}

void generateGroups()
{   
    unsigned int i = 2;
    while(i < 16)
    {
        i *= 2;
        generateGroup(i);
    }
}

void normal()
{
        config.load();
        config.saveToFile("configuration.txt");

        cout << "Warehouse Line-up Optimization" << endl; 
        WarehouseOptimization wo;
       
        wo.loadData();
        wo.perform();
}

int main()
{
    try
    {
        normal();
    }
    catch (std::string e)
    {
        std::cerr << "=== ! " << e << " ! ===" << std::endl;
    }

    return 0;
}
