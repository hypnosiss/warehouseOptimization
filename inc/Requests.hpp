#pragma once

#include "Item.hpp"
#include <vector>

class Requests
{
    public:
        std::vector < Item > & operator[](int i);
        std::vector < Item > operator[](int i) const;
        unsigned int getSize() const;
        void generate();
    private:
        std::vector < std::vector < Item > > requests;        
        bool isItemExists(const std::vector<unsigned int> & request, unsigned int id);

};
