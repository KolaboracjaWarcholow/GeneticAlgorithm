//
// Created by Szymek on 19.11.2016.
//

#ifndef GENETICALGORITHM_INDIVIDUAL_H
#define GENETICALGORITHM_INDIVIDUAL_H

#include <vector>
using namespace std;

class Individual{
private:
	vector<vector<double>> featuresVector;
	vector<vector<double>> labelsVector;
	double fitnessScore = 0;
	double accuracy=0;
	long sizeOfIndividual;
	static long count;
	long serialNumber;
public:

	long getSerialNumber() const{
		return serialNumber;
	}

	double getAccuracy() const{
		return accuracy;
	}


	void setSerialNumber();

	Individual();

	Individual(vector<vector<double>> &featuresVector,
	           vector<vector<double>> &labelsVector);

	void setScore(double newScore);

	vector<vector<double>> &getFeaturesVector(){
		return featuresVector;
	}

	long getSizeOfIndividual();

	void setSizeOfIndividual(){
		Individual::sizeOfIndividual = featuresVector.size();
	}

	vector<vector<double>> &getLabelsVector(){
		return labelsVector;
	};

    double getFitnessScore();

	void setFitnessScore(double accuracy, double sizeOfTrainingSet, double weightForSize,
		                     double weightForAccuracy);

    friend void crossoverIndividuals(double crossoverRatio, Individual &firstIndividual, Individual &secondIndividual);

	virtual ~Individual(){ };

    void ChangeFeature(int index, vector<double> new_feature);

    void ChangeLabel(int index, vector<double> new_label);

	void setAccuracy(double accuracy){
		Individual::accuracy = accuracy;
	}
};


#endif //GENETICALGORITHM_INDIVIDUAL_H

