#pragma once
#include <string>
#include <vector>
#include <random>

struct Location
{
	std::string mName = "";
	double mLatitude = 0;
	double mLongitude = 0;
};

struct Population
{
	std::vector<std::vector<int>> mMembers;
};

std::vector<Location> GetLocations(std::string fileName);
std::vector<int> GenerateOnePopulation(int locationsSize, std::mt19937& myRand);//depend on random, cannot have unit test
std::pair<int, double> ComputeFitness(std::vector<std::pair<int, double>> &fitnesses, std::vector<int> individual, std::vector<std::vector<int> > population, std::vector<Location> locations);
double HaversineDistance(int start, int end, std::vector<Location> locations);
std::vector<double> GenerateProbabilityVector(std::vector<std::pair<int, double> > fitnesses, std::vector<std::vector<int> >& population);
std::pair<int, int> GenerateParents(std::vector<double> normalizedProbability, std::mt19937& myRand);//depend on random, cannot have unit test
std::vector<int> Crossover(std::vector<std::vector<int> >&sons, std::vector<std::vector<int> > population, std::mt19937& myRand, std::pair<int, int>parents, int mutationChance);//depend on random, cannot have unit test
std::vector<int> CrossoverHelper(std::vector<std::vector<int> > population, int firstParent, int secondParent, int crossoverIndex);
int SelectParent(double randomValue, std::vector<double> probabilities);//depend on random, cannot have unit test
bool SortByFitness(std::pair<int, double> pair1, std::pair<int, double> pair2);
