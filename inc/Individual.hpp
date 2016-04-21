#pragma once

#include <vector>
#include <unordered_map>

struct Item
{
    unsigned int productId;
    int amount;
};
using Requests = std::vector < std::vector < Item > >;

class Individual
{
    public:
        unsigned int calculateFitnessFunction(Requests request);

        Item operator[](const unsigned int & index) const;
        Item& operator[](unsigned int index);
        void addItem(unsigned int id, const Item & item);
        unsigned int getSize() const;
        bool isItemExists(unsigned int id) const;

    private:
        std::unordered_map <unsigned int, Item > individual;
        Individual lessRequests(const Requests & requests) const;
};

