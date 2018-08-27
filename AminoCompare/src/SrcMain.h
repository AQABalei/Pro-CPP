#pragma once
#include <string>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <vector>
#include <tbb/parallel_invoke.h>
#include "sha1.h"

void ProcessCommandArgs(int argc, const char* argv[]);

void BruteForce(std::unordered_map<std::string, std::string>& unsolved, std::string start, std::string end);
std::vector<int> PwdStrToVec(std::string pwdStr);
std::string VecToPwdStr(std::vector<int> pwdVec);
