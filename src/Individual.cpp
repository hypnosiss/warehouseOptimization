#include "Individual.hpp"
#include "Configuration.hpp"

Individual::Individual():penalty(0)
{

}

unsigned int Individual::calculateFitnessFunction(const Requests & requests, const Products & products)
{
    Individual updatedIndividual = lessRequests(requests);
    int tmpFitnessValue=0;
    
    for (const auto & pair : updatedIndividual.individual)
    {
        const Item & item = pair.second;
        const Product & product = products[item.productId];
        tmpFitnessValue += item.amount * static_cast<int>(product.weight); 
    }

    tmpFitnessValue -= updatedIndividual.penalty;

    fitnessValue = tmpFitnessValue;
    return fitnessValue;
}


Individual Individual::lessRequests(const Requests & requests) const
{
    Individual ind = *this;
    for (size_t i=0; i < requests.getSize(); i++)
    {
        const std::vector < Item > & items = requests[i];

        for (const Item & itemFromRequest: items)
        {   
            if (!ind.isItemExists(itemFromRequest.productId))
            {
                ind.createNewItemFromRequest(itemFromRequest);
            }
            else
            {
                ind.updateBaseOnItem(itemFromRequest);
            }
        }
    }
    return ind;
}

void Individual::updateBaseOnItem(const Item & item)
{
    Item & itemFromIndividual = individual[item.productId];
    itemFromIndividual.amount -= item.amount;
    if (itemFromIndividual.amount <= 0)
        increasePenalty();
}

void Individual::createNewItemFromRequest(const Item & item) 
{
    Item newItem;
    newItem.productId = item.productId;
    newItem.amount = item.amount * (-1);
    addItem(newItem.productId, newItem);
    increasePenalty();
}

void Individual::increasePenalty()
{
    penalty += config.penalty;
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
