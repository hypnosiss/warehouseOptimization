#include "gmock/gmock.h"
#include "Population.hpp"
#include "Configuration.hpp"
#include <string>
#include "Helpers.hpp"
#include "HelpersMock.hpp"

using ::testing::Return;
using ::testing::_;

class TestablePopulation: public Population
{
    public:
        using Population::population;
};


class PopulationTest: public testing::Test
{
    protected:
        TestablePopulation population;
        unsigned int amountOfPopulation, productId, amount;

        virtual void SetUp()
        {
            config.maxPiecesPerItem = 10;
            config.maxTypesOfProducts = 11;
            config.maxWeightOfItem = 12;
            amountOfPopulation = 1;
            productId = 1;
            amount = 2;
        }

        virtual void TearDown()
        {

        }
};

TEST_F(PopulationTest, DontGenerateEmptyPopulation)
{
    ASSERT_THROW(population.generatePopulation(0), std::string);
}
/*
TEST_F(PopulationTest, GenerateNotEmptyPopulation)
{
    for (unsigned int i = 0; i < amountOfPopulation; i++)
    {
        EXPECT_CALL(helpers, getRandNumber(12,14))
             .WillOnce(Return(productId))
             .WillOnce(Return(amount));
    }

    population.generatePopulation(amountOfPopulation);
    
    for (unsigned int i = 0; i < amountOfPopulation; i++)
    {
        Individual ind = population.population[i];
        ASSERT_EQ(productId, ind.productId);
        ASSERT_EQ(amount, ind.amount);
    }
}*/
