#include "catch.hpp"
#include "SrcMain.h"
#include <string>
#include <chrono>

// Helper function declarations (don't change these)
extern bool CheckFileMD5(const std::string& fileName, const std::string& expected);
extern bool CheckTextFilesSame(const std::string& fileNameA, 
	const std::string& fileNameB);

// TODO:
// Add test cases for your functions here!!
// (You will want to make multiple test cases with different sections)
TEST_CASE("Function test cases", "[student]")
{
    SECTION("PwdStrToVec")
    {
        std::string input = "a279";
        std::vector<int> output = PwdStrToVec(input);
        std::vector<int> expected;
        expected.push_back(0);
        expected.push_back(28);
        expected.push_back(33);
        expected.push_back(35);
        
        bool result = (output == expected);
        REQUIRE(result);
    }
    
    SECTION("VecToPwdStr")
    {
        std::vector<int> input(3, -1);
        input.push_back(0);
        std::string output = VecToPwdStr(input);
        std::string expected = "a";
        bool result = (output == expected);
        REQUIRE(result);
    }
    
    SECTION("BruteForce")
    {
        std::unordered_map<std::string, std::string> test;
        test.insert({"a78cb8df129f590ee667a7a0949327760917344c", "??"});
        BruteForce(test, "qaaa", "t999");
        bool result = (test["a78cb8df129f590ee667a7a0949327760917344c"] == "sj12");
        REQUIRE(result);
    }
}

// Provided file tests
// (Once you pass the first section, comment out the other)
TEST_CASE("File tests", "[student]")
{
    SECTION("Dictionary only")
    {
        const char* argv[] = {
            "tests/tests",
            "input/d2.txt",
            "input/pass-dict.txt"
        };
        ProcessCommandArgs(3, argv);
        bool result = CheckTextFilesSame("solved.txt", "expected/dict-solved.txt");
        REQUIRE(result);
    }

    SECTION("Brute force only")
    {
        const char* argv[] = {
            "tests/tests",
            "input/d2.txt",
            "input/pass-brute.txt"
        };
        ProcessCommandArgs(3, argv);
        bool result = CheckTextFilesSame("solved.txt", "expected/brute-solved.txt");
        REQUIRE(result);
    }

    SECTION("Full")
    {
        const char* argv[] = {
            "tests/tests",
            "input/d8.txt",
            "input/pass-full.txt"
        };
        ProcessCommandArgs(3, argv);
        bool result = CheckTextFilesSame("solved.txt", "expected/full-solved.txt");
        REQUIRE(result);
    }

    SECTION("Full - Timed in Release")
    {
        const char* argv[] = {
            "tests/tests",
            "input/d8.txt",
            "input/pass-full.txt"
        };
        auto start = std::chrono::high_resolution_clock::now();
        ProcessCommandArgs(3, argv);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        float seconds = duration / 1000000000.0f;
        bool result = CheckTextFilesSame("solved.txt", "expected/full-solved.txt");
        REQUIRE(result);
        WARN("****Full timed test took: " << seconds << "s****");
        REQUIRE(seconds < 2.5f);
    }
}
