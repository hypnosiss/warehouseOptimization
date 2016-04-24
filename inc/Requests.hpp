#pragma once

#include "Item.hpp"
#include <vector>
#include <string>

class Requests
{
    public:
        std::vector < Item > & operator[](int i);
        std::vector < Item > operator[](int i) const;
        unsigned int getSize() const;
        void generate();
        void loadFromFile(std::string fileName);
        void saveToFile(std::string fileName) const;
    private:
        std::vector < std::vector < Item > > requests;        
        bool isItemExists(const std::vector<unsigned int> & request, unsigned int id);

};
