#include "TSP.h"
#include <fstream>
#include <algorithm>
#include <cmath>
#include <iterator>
#include <numeric>
#include <sstream>
#include <iostream>

std::vector<Location> GetLocations(std::string fileName)//generate location vector
{
    std::vector<Location> locations;
    std::ifstream input(fileName.c_str());
    if(!input.fail())
    {
        std::string line;
        std::stringstream ss;
        while(static_cast<bool>(getline(input, line)))
        {
            ss << line;
            Location tempLocation;
            while(ss.good())
            {
                std::string part;
                getline(ss, part, ',');
                if(tempLocation.mName.empty())
                {
                    tempLocation.mName = part;
                }
                else if(tempLocation.mLatitude == 0)
                {
                    tempLocation.mLatitude = std::stod(part);
                }
                else if(tempLocation.mLongitude == 0)
                {
                    tempLocation.mLongitude = std::stod(part);
                }
            }
            ss.clear();
            locations.push_back(tempLocation);
        }
    }
    return locations;
}

std::vector<int> GenerateOnePopulation(int locationsSize, std::mt19937& myRand)//generate an individual path
{
    std::vector<int> onePop(locationsSize);
    std::iota (onePop.begin(),onePop.end(), 0);
    std::shuffle(onePop.begin()+1, onePop.end(), myRand);
    return onePop;
}

std::pair<int, double> ComputeFitness(std::vector<std::pair<int, double> > &fitnesses, std::vector<int> individual, std::vector<std::vector<int> > population, std::vector<Location> locations)// compute fitness for a specific path and push into a fitness vector
{
    std::pair<int, double> individualNumAndFitness;
    auto it = std::find(population.begin(), population.end(), individual);
    auto index = std::distance(population.begin(), it);
    individualNumAndFitness.first = index;
    std::vector<double> distances;
    
    std::adjacent_difference(individual.begin(), individual.end(), std::back_inserter(distances), [&locations](int first, int second)
    {
        return HaversineDistance(first, second, locations);
    });
    distances.push_back(HaversineDistance(individual[individual.size()-1], individual[0], locations));
    double fitness = std::accumulate(distances.begin(), distances.end(), 0.0);
    individualNumAndFitness.second = fitness;
    if(!fitnesses.empty())
    {
        individualNumAndFitness.first = fitnesses[fitnesses.size()-1].first + 1;
    }
    fitnesses.push_back(individualNumAndFitness);
    return individualNumAndFitness;
}

double HaversineDistance(int start, int end, std::vector<Location> locations)//calculate haversine distance
{
    double lon1 = locations[start].mLongitude * 0.0174533;
    double lon2 = locations[end].mLongitude * 0.0174533;
    double lat1 = locations[start].mLatitude * 0.0174533;
    double lat2 = locations[end].mLatitude * 0.0174533;
    double dlon = lon1 - lon2;
    double dlat = lat1 - lat2;
    double a = pow(sin(dlat/2),2) + cos(lat1) * cos(lat2) * pow(sin(dlon/2), 2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    return 3961 * c;
}

std::vector<double> GenerateProbabilityVector(std::vector<std::pair<int, double> > fitnesses, std::vector<std::vector<int> >& population)
{
    std::sort(fitnesses.begin(), fitnesses.end(), SortByFitness);
    std::vector<double> probabilities(population.size());
    std::generate(probabilities.begin(), probabilities.end(), [&fitnesses]()
    {
        return 1.0/fitnesses.size();
    });
    int highestFitnessIndex = fitnesses[0].first;
    int secondHighestFitnessIndex = fitnesses[1].first;
    probabilities[highestFitnessIndex] *= 6.0;
    probabilities[secondHighestFitnessIndex] *= 6.0;
    std::vector<int> topHalfIndex;
    std::for_each(fitnesses.begin()+2, fitnesses.begin()+(fitnesses.size()/2), [&topHalfIndex](std::pair<int, double> fit)
    {
        return topHalfIndex.push_back(fit.first);
    });
    std::for_each(topHalfIndex.begin(), topHalfIndex.end(), [&probabilities](int tempIndex)
    {
        return probabilities[tempIndex] *= 3.0;
    });
    double sumOfProbabilities = std::accumulate(probabilities.begin(), probabilities.end(), 0.0);
    std::vector<double> normalizedProbability(probabilities.size());
    std::transform(probabilities.begin(), probabilities.end(), normalizedProbability.begin(), [sumOfProbabilities](double unNormalized)
    {
        return unNormalized/sumOfProbabilities;
    });
    return normalizedProbability;
}

std::pair<int, int> GenerateParents(std::vector<double> normalizedProbability, std::mt19937& myRand)//generate one parent pair
{
    std::pair<int, int> parents;
    std::uniform_real_distribution<double> generator(0, 1);
    double randomDouble1 = generator(myRand);
    double randomDouble2 = generator(myRand);
    parents.first = SelectParent(randomDouble1, normalizedProbability);
    parents.second = SelectParent(randomDouble2, normalizedProbability);
    return parents;
}

int SelectParent(double randomValue, std::vector<double> probabilities)//generate parent helper
{
    std::vector<double> partialSum;
    std::partial_sum(probabilities.begin(), probabilities.end(), std::back_inserter(partialSum));
    std::vector<double>::iterator it = std::find_if(partialSum.begin(), partialSum.end(), [randomValue](double currValue)
    {
        return currValue >= randomValue;
    });
    int index = std::distance(partialSum.begin(), it);
    return index;
}

std::vector<int> Crossover(std::vector<std::vector<int> >&sons, std::vector<std::vector<int> > population, std::mt19937& myRand, std::pair<int, int> parents, int mutationChance)
{
    double castedChance = (static_cast<double>(mutationChance))/100.0;
    std::vector<int> result;
    std::uniform_int_distribution<int> generator(1, population[0].size()-2);
    int crossoverIndex = generator(myRand);
    std::uniform_int_distribution<int> zeroToOne(0,1);
    int oneOrZero = zeroToOne(myRand);
    if(oneOrZero == 1)
    {
        result = CrossoverHelper(population, parents.first, parents.second, crossoverIndex);
    }
    else
    {
        result = CrossoverHelper(population, parents.second, parents.first, crossoverIndex);
    }
    std::uniform_real_distribution<double> mutationDecision(0, 1);
    double mutationOrNot = mutationDecision(myRand);
    if(mutationOrNot <= castedChance)
    {
        std::uniform_int_distribution<int> mutationGenerator(1, population[0].size()-1);
        int firstIndex = mutationGenerator(myRand);
        int secondIndex = mutationGenerator(myRand);
        std::swap(result[firstIndex], result[secondIndex]);
    }
    sons.push_back(result);
    return result;
}

std::vector<int> CrossoverHelper(std::vector<std::vector<int> > population, int firstParent, int secondParent, int crossoverIndex)
{
    std::vector<int> result;
    std::copy(population[firstParent].begin(), population[firstParent].begin()+crossoverIndex+1, std::back_inserter(result));
    std::copy_if(population[secondParent].begin(), population[secondParent].end(), std::back_inserter(result), [&result](int individual)
    {
        return std::find(result.begin(), result.end(), individual) == result.end();
    });
    return result;
}

bool SortByFitness(std::pair<int, double> pair1, std::pair<int, double> pair2)
{
    return (pair1.second < pair2.second);
}

