#include "gmock/gmock.h"
#include "Helpers.hpp"

class HelpersMock: public Helpers
{
    public:
        MOCK_METHOD2(getRandNumber, int(unsigned int from, unsigned int to));
};
