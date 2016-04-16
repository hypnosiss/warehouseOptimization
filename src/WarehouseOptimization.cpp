#include "WarehouseOptimization.hpp"
#include "Configuration.hpp"
#include "Helpers.hpp"

void WarehouseOptimization::generateProducts()
{
    products.clear();
    for (unsigned int i; i < config.maxTypesOfProducts; i++)
    {
        unsigned int weight = static_cast<unsigned int>(getRandNumber(0, config.maxWeightOfItem));
        products.push_back(Product{.weight=weight});
    }
}

