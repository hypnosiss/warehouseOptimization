#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Products.hpp"
#include "Individual.hpp"
#include "Configuration.hpp"
#include "WarehouseOptimization.hpp"
using namespace std;

int main()
{
    try
    {
        config.load();
        config.saveToFile("configuration.txt");
       
        cout << "Warehouse Line-up Optimization" << endl; 
        WarehouseOptimization wo;
       
        wo.loadData();
        wo.perform();
    } 
    catch (std::string e)
    {
        std::cerr << "=== ! " << e << " ! ===" << std::endl;
    }

    return 0;
}
