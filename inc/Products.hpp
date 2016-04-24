#pragma once
#include <vector>
#include <string>

struct Product
{
    unsigned int weight;
};

class Products
{
    public:
        Product & operator[](int i);
        Product operator[](int i) const;
        void generate();
        void loadFromFile(std::string fileName);
        void saveToFile(std::string fileName) const;
        unsigned int getSize() const;

    private:
        std::vector < Product > products;
};

