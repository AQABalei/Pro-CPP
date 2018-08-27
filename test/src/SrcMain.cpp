#include "SrcMain.h"
#include <iostream>
#include <random>
#include "TSP.h"
#include <fstream>
#include <algorithm>

void ProcessCommandArgs(int argc, const char* argv[])
{
	// TODO
    //Parse command line arguments
    std::string inputFileName = argv[1];
    int popSize = atoi(argv[2]);
    int generations = atoi(argv[3]);
    int mutationChance = atoi(argv[4]);
    int seed = atoi(argv[5]);
    std::ofstream output;
    
    //read input file
    std::vector<Location> locations = GetLocations(inputFileName);
    std::mt19937 myRand(seed);
    std::vector<std::vector<int> >population(popSize);
    std::vector<std::pair<int, double> > fitnesses;
    std::vector<std::pair<int, int> > parentsPairs(popSize);
    std::vector<std::vector<int> > firstGeneration;
    int locationsSize = locations.size();
    std::generate_n(population.begin(), popSize, [&locationsSize, &myRand]()//generate initial population
    {
        return GenerateOnePopulation(locationsSize, myRand);
    });
    std::for_each(population.begin(), population.end(), [&fitnesses, &population, &locations](std::vector<int> individual){//compute fitness for the initial population
        return ComputeFitness(fitnesses, individual, population, locations);
    });
    std::vector<double> finalProbability = GenerateProbabilityVector(fitnesses,population);//Generate Probability Vector
    std::generate_n(parentsPairs.begin(), popSize, [&myRand, &finalProbability]()//Generate Parent Pairs
    {
        return GenerateParents(finalProbability, myRand);
    });
    output.open("log.txt");
    output << "INITIAL POPULATION:" << std::endl;
    for(int i=0; i<population.size(); ++i)
    {
        for(int j=0; j<population[i].size(); ++j)
        {
            if(j != population[i].size() - 1)
            {
                output << population[i][j] << ",";
            }
            else
            {
                output << population[i][j];
            }
        }
        output << std::endl;
    }
    output << "FITNESS:" << std::endl;
    for(int i=0; i<fitnesses.size(); ++i)
    {
        output << fitnesses[i].first << ":" << fitnesses[i].second << std::endl;
    }
    output << "SELECTED PAIRS:" << std::endl;
    for(int i=0; i<parentsPairs.size(); ++i)
    {
        output << "(" << parentsPairs[i].first << "," << parentsPairs[i].second << ")" << std::endl;
    }
    std::vector<double> outsideProbability;
    std::vector<std::vector<int> > lastGeneration;
    std::vector<std::pair<int, double> > lastFitness;
    std::vector<std::pair<int, int> > lastParentsPairs(popSize);
    for(int i=0; i<generations; ++i)//start printing to the log.txt
    {
        std::vector<std::vector<int> > thisGeneration;
        std::vector<std::pair<int, double> > thisFitness;
        std::vector<std::pair<int, int> > thisParentsPairs(popSize);
        if(i == 0)
        {
            std::for_each(parentsPairs.begin(), parentsPairs.end(), [&thisGeneration, &population, &myRand, mutationChance](std::pair<int, int> oneParents)
            {
                return Crossover(thisGeneration, population, myRand, oneParents, mutationChance);
            });
        }
        else
        {
            std::for_each(lastParentsPairs.begin(), lastParentsPairs.end(), [&thisGeneration, &lastGeneration, &myRand, mutationChance](std::pair<int, int> oneParents)
            {
                return Crossover(thisGeneration, lastGeneration, myRand, oneParents, mutationChance);
            });
        }
        lastGeneration = thisGeneration;
        output << "GENERATION: " << i+1 << std::endl;
        for(int j=0; j<lastGeneration.size(); ++j)
        {
            for(int k=0; k<lastGeneration[j].size(); ++k)
            {
                if(k != lastGeneration[j].size() - 1)
                {
                    output << lastGeneration[j][k] << ",";
                }
                else
                {
                    output << lastGeneration[j][k];
                }
            }
            output << std::endl;
        }
        std::for_each(lastGeneration.begin(), lastGeneration.end(), [&thisFitness, &lastGeneration, &locations](std::vector<int> individual)
        {
            return ComputeFitness(thisFitness, individual, lastGeneration, locations);
        });
        lastFitness = thisFitness;
        output << "FITNESS:" << std::endl;
        for(int j=0; j<lastFitness.size(); ++j)
        {
            output << lastFitness[j].first << ":" << lastFitness[j].second << std::endl;
        }
        outsideProbability = GenerateProbabilityVector(lastFitness, lastGeneration);
        if(i != generations - 1)
        {
            std::generate_n(thisParentsPairs.begin(), popSize, [&myRand, &outsideProbability]()
            {
                return GenerateParents(outsideProbability, myRand);
            });
            lastParentsPairs = thisParentsPairs;
            output << "SELECTED PAIRS:" << std::endl;
            for(int j=0; j<lastParentsPairs.size(); ++j)
            {
                output << "(" << lastParentsPairs[j].first << "," << lastParentsPairs[j].second << ")" << std::endl;
            }
        }
        else
        {
            std::vector<std::pair<int, double> >::iterator it = std::min_element(lastFitness.begin(), lastFitness.end(), [](std::pair<int, double> pair1, std::pair<int, double> pair2)
            {
                return pair1.second < pair2.second;
            });
            output << "SOLUTION:" << std::endl;
            for(int j = 0; j<lastGeneration[it->first].size(); ++j)
            {
                output << locations[lastGeneration[it->first][j]].mName << std::endl;
            }
            output << locations[0].mName << std::endl;
            output << "DISTANCE: " << it->second << " miles" << std::endl;
        }
    }
}
