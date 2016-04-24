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
            config.amountOfTypesOfProducts = 11;
            config.maxWeightOfItem = 12;
            config.amountOfPopulation = 2;
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
    config.amountOfPopulation = 0;
    ASSERT_THROW(population.generate(), std::string);
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

    population.generate(amountOfPopulation);
    
    for (unsigned int i = 0; i < amountOfPopulation; i++)
    {
        Individual ind = population.population[i];
        ASSERT_EQ(productId, ind.productId);
        ASSERT_EQ(amount, ind.amount);
    }
}*/
