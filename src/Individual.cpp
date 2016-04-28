#include "Individual.hpp"
#include "Helpers.hpp"
#include "Configuration.hpp"
#include <iostream>
#include <algorithm>

Individual::Individual():penalty(0)
{
    searchListOfProductsIds.resize(config.amountOfTypesOfProducts);
    unsigned int index=0;
    for_each(searchListOfProductsIds.begin(), searchListOfProductsIds.end(), 
                  [&index](unsigned int &x) { x=index++; });
}

unsigned int Individual::calculateFitnessFunction(const Requests & requests, const Products & products)
{
    Individual updatedIndividual = lessRequests(requests);
#if DEBUG==1
    std::cout << "OriginalIndividual=" << getSize() << ",updatedIndividual="<<updatedIndividual.getSize() << std::endl;
#endif
    int tmpFitnessValue=0;
    
    for (const auto & pair : updatedIndividual.individual)
    {
        const Item & item = pair.second;
        const Product & product = products[item.productId];
        if (item.amount > 0)
            tmpFitnessValue += item.amount*static_cast<int>(product.weight); 
    }
#if DEBUG==1
    std::cout << "penalty="<<updatedIndividual.penalty << std::endl;
#endif
    tmpFitnessValue -= updatedIndividual.penalty;

    fitnessValue = tmpFitnessValue;
    return fitnessValue;
}

int Individual::getFitnessValue() const
{
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
    //if (individual.size() <= 0 )
      //  return false;

    auto t = individual.find(id);
    return (t != individual.end());
}

unsigned int Individual::getRandProductId()
{
    unsigned int randomNumber = static_cast<unsigned int>(Helpers::getRandNumber(0, searchListOfProductsIds.size()));
    std::list<unsigned int>::iterator randomElement = searchListOfProductsIds.begin();
    std::advance(randomElement, randomNumber);

    unsigned int productId = *randomElement;
    searchListOfProductsIds.erase(randomElement);
    return productId;
}

void Individual::addItem(unsigned int id, const Item & item)
{
    individual.insert({id, item});
}

unsigned int Individual::getSize() const
{
    return individual.size();
}

std::ostream & operator << (std::ostream &os, const Individual & ind)
{
    os << ind.getSize() << " ";
    for (const auto & pair : ind.individual)
    {
        Item item = pair.second;
        os << item.productId << " " << item.amount << " ";
    }
    os << std::endl;
    return os;
}
