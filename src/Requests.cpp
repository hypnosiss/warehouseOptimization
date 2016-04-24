#include "Requests.hpp"
#include "Configuration.hpp"
#include "Helpers.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>

std::vector < Item > & Requests::operator[](int i)
{
    return requests[i];
}

std::vector < Item >  Requests::operator[](int i) const
{
    return requests[i];
}

unsigned int Requests::getSize() const
{
    return requests.size();
}

void Requests::generate()
{
    requests.clear();
    for (unsigned int i=0; i < config.amountOfRequests; i++)
    {
        unsigned int amountOfItems = static_cast<unsigned int>(Helpers::getRandNumber(config.minItemsInRequest, config.maxItemsInRequest));
        std::vector < Item > request;
        std::vector <unsigned int> ids;
        for (unsigned int j=0; j < amountOfItems; j++)
        {
            unsigned int productId;
            do 
            {//todo: may freeze
                productId = static_cast<unsigned int>(Helpers::getRandNumber(0, config.amountOfTypesOfProducts));
            }
            while (isItemExists(ids, productId));
            ids.push_back(productId);

            int amount = Helpers::getRandNumber(1, config.maxPiecesPerItemInRequest);
            request.push_back(Item{.productId=productId, .amount=amount});
        }
        ids.clear();
        requests.push_back(request);
    }
}

void Requests::loadFromFile(std::string fileName)
{
    requests.clear();
    std::ifstream file(fileName);
    file >> config.amountOfRequests;

    for (unsigned int i=0; i < config.amountOfRequests; i++)
    {
        unsigned int amountOfItems;
        file >> amountOfItems;
        std::vector <Item> request;
        for (unsigned int j=0; j < amountOfItems; j++)
        {
            Item item;
            file >> item.productId;
            file >> item.amount;
            request.push_back(item);
        }
        requests.push_back(request);
    }
    file.close();
}

void Requests::saveToFile(std::string fileName) const
{
    std::ofstream file(fileName);
    file << requests.size() << std::endl;

    for (const std::vector < Item > & request : requests)
    {
        file << request.size() << " ";
        for (const Item & item : request)
        {
            file << item.productId << " " << item.amount << " ";
        }
        file << std::endl;
    }
    file.close();
}

bool Requests::isItemExists(const std::vector<unsigned int> & request, unsigned int id)
{
    auto it = std::find(request.begin(), request.end(), id);
    return (it != request.end());
}
