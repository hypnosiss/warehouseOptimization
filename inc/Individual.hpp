#pragma once

#include "Product.hpp"
#include "Requests.hpp"
#include <vector>
#include <unordered_map>

class Individual
{
    public:
        Individual();
        unsigned int calculateFitnessFunction(const Requests & requests, const Products & products);

        Item operator[](const unsigned int & index) const;
        Item& operator[](unsigned int index);
        void addItem(unsigned int id, const Item & item);
        unsigned int getSize() const;
        bool isItemExists(unsigned int id) const;

    private:
        std::unordered_map <unsigned int, Item > individual;
        int penalty;
        int fitnessValue;

        void increasePenalty();
        void updateBaseOnItem(const Item & item);
        void createNewItemFromRequest(const Item & item);
        Individual lessRequests(const Requests & requests) const;
};

