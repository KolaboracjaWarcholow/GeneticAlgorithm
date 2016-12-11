//
// Created by Szymek on 19.11.2016.
//

#ifndef GENETICALGORITHM_GENETICALGORITHM_H
#define GENETICALGORITHM_GENETICALGORITHM_H

#include <iostream>
#include "Algorithm.h"
#include "Population.h"

template <typename featureType, typename labelType>
class GeneticAlgorithm : public Algorithm<featureType, labelType>{

public:
	int sizeOfPopulation = 100;
	int sizeOfIndyvidual = 100;
	double mutationCoefficient = 0.01;
	Population<featureType, labelType> population;
	GeneticAlgorithm(const Dataset<featureType, labelType> &dataset) : Algorithm<featureType, labelType>(dataset){ }

	void run(){
		population.CreateInitialPopulation(Algorithm<featureType, labelType>::dataset, sizeOfPopulation,
		                                   sizeOfIndyvidual);
		std::cout << "Initial population created" << std::endl;
	}
};


#endif //GENETICALGORITHM_GENETICALGORITHM_H
