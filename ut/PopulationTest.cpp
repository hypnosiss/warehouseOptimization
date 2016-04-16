#include "gmock/gmock.h"
#include "Population.hpp"
#include "Configuration.hpp"

using ::testing::Return;

class TestablePopulation: public Population
{
    public:
        using Population::population;
};

class PopulationTest: public testing::Test
{
    protected:
        TestablePopulation population;
        unsigned int amountOfPopulation;

        virtual void SetUp()
        {
            config.maxPiecesPerItem = 10;
            config.maxTypesOfProducts = 11;
            config.maxWeightOfItem = 12;
            amountOfPopulation = 13;
        }

        virtual void TearDown()
        {

        }
};

TEST_F(PopulationTest, GenerateNotEmptyPopulation)
{
    int ret = population.generatePopulation(amountOfPopulation);
    ASSERT_EQ(amountOfPopulation, population.population.size());
    ASSERT_EQ(2, ret);
}
