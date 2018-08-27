#include "catch.hpp"
#include "SrcMain.h"
#include "TSP.h"
#include <string>

// Don't change this
#ifdef _MSC_VER
const std::string SamplePath("sampleoutput/win/");
#elif __APPLE__
const std::string SamplePath("sampleoutput/mac/");
#else
const std::string SamplePath("sampleoutput/linux/");
#endif
// Helper function declarations (don't change these)
extern bool CheckFileMD5(const std::string& fileName, const std::string& expected);
extern bool CheckTextFilesSame(const std::string& fileNameA, 
	const std::string& fileNameB);

// TODO:
// Add test cases for your functions here!!
// (You will want to make multiple test cases with different sections)
TEST_CASE("Function test cases", "[student]")
{
    SECTION("GET LOCATION")
    {
        std::vector<Location> output = GetLocations("input/test.txt");
        std::vector<Location> expected;
        Location loc1, loc2;
        loc1.mName = "LAX Airport";
        loc1.mLatitude = 33.941845;
        loc1.mLongitude = -118.408635;
        loc2.mName = "Tommy Trojan";
        loc2.mLatitude = 34.020547;
        loc2.mLongitude = -118.285397;
        expected.push_back(loc1);
        expected.push_back(loc2);
        bool result = true;
        for(int i=0; i<expected.size(); ++i)
        {
            if(output[i].mName != expected[i].mName || output[i].mLongitude != expected[i].mLongitude || output[i].mLatitude != expected[i].mLatitude)
            {
                result = false;
            }
        }
        REQUIRE(result);
    }
    
    SECTION("COMPUTE FITNESS")
    {
        std::vector<std::vector<int> >population(2);
        int arrIndividual1[] = {1,2,3,19};
        int arrIndividual2[] = {6,13,1,2};
        std::vector<int> vecIndividual1(arrIndividual1, arrIndividual1 + sizeof(arrIndividual1) / sizeof(int));
        std::vector<int> vecIndividual2(arrIndividual2, arrIndividual2 + sizeof(arrIndividual2) / sizeof(int));
        population[0] = vecIndividual1;
        population[1] = vecIndividual2;
        std::vector<std::pair<int, double>> fitnesses;
        std::vector<Location> locations = GetLocations("input/locations.txt");
        std::pair<int, double> output = ComputeFitness(fitnesses, vecIndividual1, population, locations);
        std::pair<int, double> expected;
        expected.first = 0;
        expected.second = 67.217923914415607;
        REQUIRE(output.second == Approx(expected.second));
    }
    
    SECTION("HAVERSINE DISTANCE")
    {
        std::vector<Location> testLocations = GetLocations("input/locations.txt");
        double output = HaversineDistance(0, 1, testLocations);
        double expected =8.9170522271021948;
        bool result = (output == expected);
        REQUIRE(result);
    }
    
    SECTION("SORT BY FITNESS")
    {
        std::pair<int, double> smallerDouble, biggerDouble;;
        smallerDouble.first = 1;
        smallerDouble.second = 0.05;
        biggerDouble.first = 2;
        biggerDouble.second = 0.1;
        bool result = (smallerDouble.second < biggerDouble.second);
        REQUIRE(result);
    }
    
    SECTION("CROSSOVER HELPER")
    {
        std::vector<std::vector<int> >population(2);
        int arrIndividual1[] = {1,2,3,19};
        int arrIndividual2[] = {6,13,1,2};
        int afterCross[] = {1,2,6,13};
        std::vector<int> vecIndividual1(arrIndividual1, arrIndividual1 + sizeof(arrIndividual1) / sizeof(int));
        std::vector<int> vecIndividual2(arrIndividual2, arrIndividual2 + sizeof(arrIndividual2) / sizeof(int));
        population[0] = vecIndividual1;
        population[1] = vecIndividual2;
        std::vector<int> output = CrossoverHelper(population, 0, 1, 1);
        std::vector<int> expected(afterCross, afterCross + sizeof(afterCross) / sizeof(int));
        bool result = true;
        for(int i=0; i<expected.size(); ++i)
        {
            if(output[i] != expected[i])
            {
                result = false;
            }
        }
        REQUIRE(result);
    }
}

// Provided Complete file test cases
// (Once you pass the first section, comment out the other)
TEST_CASE("Full file test cases", "[student]")
{
    SECTION("input/locations.txt 8 5 10 1337")
    {
        const char* argv[] = {
            "tests/tests",
            "input/locations.txt",
            "8",
            "5",
            "10",
            "1337"
        };
        ProcessCommandArgs(6, argv);
        bool result = CheckTextFilesSame("log.txt", SamplePath + "log_8_5_10_1337.txt");
        REQUIRE(result);
    }
    SECTION("input/locations.txt 32 20 5 5741328")
    {
        const char* argv[] = {
            "tests/tests",
            "input/locations.txt",
            "32",
            "20",
            "5",
            "5741328"
        };
        ProcessCommandArgs(6, argv);
        bool result = CheckTextFilesSame("log.txt", SamplePath + "log_32_20_5_5741328.txt");
        REQUIRE(result);
    }
    SECTION("input/locations.txt 64 500 30 12165465")
    {
        const char* argv[] = {
            "tests/tests",
            "input/locations.txt",
            "64",
            "500",
            "30",
            "12165465"
        };
        ProcessCommandArgs(6, argv);
        bool result = CheckTextFilesSame("log.txt", SamplePath + "log_64_500_30_12165465.txt");
        REQUIRE(result);
    }
    SECTION("input/locations.txt 128 200 10 331988960")
    {
        const char* argv[] = {
            "tests/tests",
            "input/locations.txt",
            "128",
            "200",
            "10",
            "331988960"
        };
        ProcessCommandArgs(6, argv);
        bool result = CheckTextFilesSame("log.txt", SamplePath + "log_128_200_10_331988960.txt");
        REQUIRE(result);
    }
    SECTION("input/locations.txt 256 200 20 7410785")
    {
        const char* argv[] = {
            "tests/tests",
            "input/locations.txt",
            "256",
            "200",
            "20",
            "7410785"
        };
        ProcessCommandArgs(6, argv);
        bool result = CheckTextFilesSame("log.txt", SamplePath + "log_256_200_20_7410785.txt");
        REQUIRE(result);
    }
    SECTION("input/locations2.txt 64 200 25 49328573")
    {
        const char* argv[] = {
            "tests/tests",
            "input/locations2.txt",
            "64",
            "200",
            "25",
            "49328573"
        };
        ProcessCommandArgs(6, argv);
        bool result = CheckTextFilesSame("log.txt", SamplePath + "log_64_200_25_49328573.txt");
        REQUIRE(result);
    }
}

