#include "Requests.hpp"
#include "Configuration.hpp"
#include "Helpers.hpp"
#include <algorithm>

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
    for (unsigned int i; i < config.amountOfRequests; i++)
    {
        unsigned int amountOfItems = static_cast<unsigned int>(Helpers::getRandNumber(0, config.maxItemsInRequest));
        std::vector < Item > request;
        std::vector <unsigned int> ids;
        for (unsigned int j=0; j < amountOfItems; j++)
        {
            unsigned int productId;
            do productId = static_cast<unsigned int>(Helpers::getRandNumber(0, config.maxTypesOfProducts));
            while (!isItemExists(ids, productId));
            ids.push_back(productId);

            int amount = Helpers::getRandNumber(0, config.maxPiecesPerItemInRequest);
            request.push_back(Item{.productId=productId, .amount=amount});
        }
        ids.clear();
        requests.push_back(request);
    }
}

bool Requests::isItemExists(const std::vector<unsigned int> & request, unsigned int id)
{
    auto it = std::find(request.begin(), request.end(), id);
    return (it != request.end());
}
