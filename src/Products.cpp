#include "Products.hpp"
#include "Configuration.hpp"
#include "Helpers.hpp"
#include <fstream>
#include <iostream>

Product & Products::operator[](int i)
{
    return products[i];
}

Product Products::operator[](int i) const
{
    return products[i];
}

void Products::generate()
{
    products.clear();
    for (unsigned int i=0; i < config.amountOfTypesOfProducts; i++)
    {
        unsigned int weight = static_cast<unsigned int>(Helpers::getRandNumber(0, config.maxWeightOfItem));
        products.push_back(Product{.weight=weight});
    }
}

unsigned int Products::getSize() const
{
    return products.size();
}

void Products::loadFromFile(std::string fileName)
{
    std::ifstream file(fileName);
    products.clear();
    file >> config.amountOfTypesOfProducts;
    for (unsigned int i=0; i < config.amountOfTypesOfProducts; i++)
    {
        unsigned int weight;
        file >> weight;
        products.push_back(Product{.weight=weight});
    }
    file.close();
}

void Products::saveToFile(std::string fileName) const
{
    std::ofstream file(fileName);
    file << products.size() << std::endl;
    for (const Product & product : products)
    {
        file << product.weight << " ";
    }

    file.close();
}
