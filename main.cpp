#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Product.hpp"
#include "Individual.hpp"

using namespace std;

vector < Product > products;
vector < Individual > population;
vector < vector < Individual > > requests;
unsigned int maxPiecesPerItem=0;
unsigned int maxWeightOfItem=0;
unsigned int maxTypesOfProducts=0;

int getRandNumber(unsigned int from, unsigned int to)
{
    srand(time(NULL));
    return (rand()%to + from); 
}

void generateProducts()
{
    products.clear();
    for (unsigned int i; i < maxTypesOfProducts; i++)
    {
        unsigned int weight = static_cast<unsigned int>(getRandNumber(0, maxWeightOfItem));
        products.push_back(Product{.weight=weight});
    }
}

void generatePopulation(unsigned int amount)
{
    for(unsigned int i=0; i < amount; i++)
    {
        unsigned int productId = static_cast<unsigned int>(getRandNumber(0, maxTypesOfProducts));
        unsigned int amount = static_cast<unsigned int>(getRandNumber(0, maxPiecesPerItem));
        
        population.push_back(Individual{.productId=productId, .amount=amount});
    }      
}

int main()
{
    cout << "Warehouse Line-up Optimization" << endl; 
    return 0;
}
