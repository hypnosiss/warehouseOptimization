#include "Individual.hpp"
/*
unsigned int Individual::calculateFitnessFunction(Requests request)
{
   
}
*/
Individual Individual::lessRequests(const Requests & requests) const
{
    Individual ind = *this;
    for (const std::vector< Item > & items: requests)
    {
        for (const Item & itemFromRequest: items)
        {   
            if (!ind.isItemExists(itemFromRequest.productId))
            {
                Item newItem;
                newItem.productId = itemFromRequest.productId;
                newItem.amount = itemFromRequest.amount * (-1);
                ind.addItem(newItem.productId, newItem);
            }
            else
            {
                Item & itemFromIndividual = ind[itemFromRequest.productId];
                itemFromIndividual.amount -= itemFromRequest.amount;
            }
        }
    }
    return ind;
}

Item Individual::operator[](const unsigned int & index) const
{
    return individual.at(index);
}

Item& Individual::operator[](unsigned int index)
{
    return individual.at(index);
}

bool Individual::isItemExists(unsigned int id) const// TODO: test it
{
    auto t = individual.find(id);
    return (t != individual.end());
}

void Individual::addItem(unsigned int id, const Item & item)
{
    individual.insert({id, item});
}

unsigned int Individual::getSize() const
{
    return individual.size();
}
