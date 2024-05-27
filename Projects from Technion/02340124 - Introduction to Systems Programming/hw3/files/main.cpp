/* #include <functional>
#include <string>
#include "TestUtils.h"

namespace HealthPointsTests {
    bool testInitialization();
    bool testArithmaticOperators();
    bool testComparisonOperators();
    bool testOutputOperator();
}

namespace QueueTests {
    bool testQueueMethods();
    bool testModuleFunctions();
    bool testExceptions();
    bool testConstQueue();
}

std::function<bool()> testsList[] = {
        HealthPointsTests::testInitialization,
        HealthPointsTests::testArithmaticOperators,
        HealthPointsTests::testComparisonOperators,
        HealthPointsTests::testOutputOperator,

        QueueTests::testQueueMethods,
        QueueTests::testModuleFunctions,
        QueueTests::testExceptions,
        QueueTests::testConstQueue
};

const int NUMBER_OF_TESTS = sizeof(testsList)/sizeof(std::function<bool()>);

int main(int argc, char *argv[])
{
    if (argc < 2) {
        for (int i = 0; i < NUMBER_OF_TESTS; ++i) {
            runTest(testsList[i], "Test " + std::to_string(i + 1));
        }
    }
    else {
        int idx = -1;
        try {
            idx = std::stoi(argv[1]) - 1;
        } catch (const std::invalid_argument &e) {
            std::cerr << "Error: invalid argument: " << argv[1] << std::endl;
            return 1;
        }
        if (idx < 0 || idx > NUMBER_OF_TESTS - 1) {
            std::cerr << "Error: index out of range: " << argv[1] << std::endl;
            return 1;
        }
        runTest(testsList[idx], "Test " + std::to_string(idx + 1));
    }
    return 0;
}
*/

/*
#include <string>
#include <iostream>
#include <vector>
#include "catch.hpp"
#include "relativeIncludes.h"


template <class T>
void readQueue(std::string& string, Queue<T> &q)
{
    std::stringstream ss;

    bool first = true;
    ss << "{" ;
    for (T& data : q)
    {
        ss << (first ? "" : ", ") << data;
        first = false;
    }
    ss << "}";
    string = ss.str();
}



int main()
{
    SECTION("Mixed Operations (with HealthPoints")
    {
        Queue<HealthPoints> healthyQ;
        for (int i = 1; i < 5; ++i)
        {
            healthyQ.pushBack(i);
        }

        int i = 1;
        for (HealthPoints &hp : healthyQ)
        {
            hp -= (i++) % 3;
        }

        std::string result;
        readQueue(result, healthyQ);
        std::string expected = "{0(1), 0(2), 3(3), 3(4)}";
        REQUIRE(result == expected);

        healthyQ.popFront();
        healthyQ.pushBack(healthyQ.front());
        healthyQ.popFront();
        readQueue(result, healthyQ);
        expected = "{3(3), 3(4), 0(2)}";
        REQUIRE(result == expected);

        healthyQ.popFront();
        healthyQ.pushBack(healthyQ.front());
        healthyQ.popFront();
        readQueue(result, healthyQ);
        expected = "{0(2), 3(4)}";
        REQUIRE(result == expected);

        healthyQ.popFront();
        healthyQ.pushBack(healthyQ.front());
        healthyQ.popFront();
        readQueue(result, healthyQ);
        expected = "{3(4)}";
        REQUIRE(result == expected);

        for (int i = 5; i < 10; ++i)
        {
            healthyQ.pushBack(i);
        }

        auto isGreaterThen7 = [](HealthPoints &hp)
        {
            return hp > 7;
        };
        Queue<HealthPoints> filterHealthQ = filter(healthyQ, isGreaterThen7);
        readQueue(result, filterHealthQ);
        expected = "{8(8), 9(9)}";
        REQUIRE(result == expected);

        filterHealthQ.pushBack(11);
        healthyQ.pushBack(12);
        filterHealthQ.popFront();

        readQueue(result, filterHealthQ);
        expected = "{9(9), 11(11)}";
        REQUIRE(result == expected);

        readQueue(result, healthyQ);
        expected = "{3(4), 5(5), 6(6), 7(7), 8(8), 9(9), 12(12)}";
        REQUIRE(result == expected);


        auto remove2HP = [](HealthPoints &hp)
        {
            hp = (-1) + hp;
            hp = hp + (-1);
        };
        transform(healthyQ, remove2HP);
        readQueue(result, healthyQ);
        expected = "{1(4), 3(5), 4(6), 5(7), 6(8), 7(9), 10(12)}";
        REQUIRE(result == expected);

        healthyQ.popFront();
        readQueue(result, healthyQ);
        expected = "{3(5), 4(6), 5(7), 6(8), 7(9), 10(12)}";
        REQUIRE(result == expected);

        healthyQ.pushBack(filterHealthQ.front());
        readQueue(result, healthyQ);
        expected = "{3(5), 4(6), 5(7), 6(8), 7(9), 10(12), 9(9)}";
        REQUIRE(result == expected);

        transform(healthyQ, remove2HP);
        readQueue(result, healthyQ);
        expected = "{1(5), 2(6), 3(7), 4(8), 5(9), 8(12), 7(9)}";
        REQUIRE(result == expected);

        readQueue(result, filterHealthQ);
        expected = "{9(9), 11(11)}";
        REQUIRE(result == expected);

        filterHealthQ = filter(healthyQ, isGreaterThen7);

        readQueue(result, filterHealthQ);
        expected = "{8(12)}";
        REQUIRE(result == expected);

        readQueue(result, healthyQ);
        expected = "{1(5), 2(6), 3(7), 4(8), 5(9), 8(12), 7(9)}";
        REQUIRE(result == expected);
    }
}
*/

#define CATCH_CONFIG_MAIN


#include "QueueUnitTests.cpp"
#include "HealthPointsUnitTests.cpp"
