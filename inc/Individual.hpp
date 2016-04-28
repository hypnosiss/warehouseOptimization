#pragma once

#include "Products.hpp"
#include "Requests.hpp"
#include <vector>
#include <list>
#include <fstream>
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
        int getFitnessValue() const;
        bool isItemExists(unsigned int id) const;
        unsigned int getRandProductId();

    private:
        std::unordered_map <unsigned int, Item > individual;
        std::list <unsigned int> searchListOfProductsIds;
        int penalty;
        int fitnessValue;

        void increasePenalty();
        void updateBaseOnItem(const Item & item);
        void createNewItemFromRequest(const Item & item);
        Individual lessRequests(const Requests & requests) const;
        friend std::ostream & operator << (std::ostream &os, const Individual & ind);
};

