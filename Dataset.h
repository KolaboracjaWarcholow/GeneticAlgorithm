//
// Created by Szymek on 09.11.2016.
//

#ifndef GENETICALGORITHM_DATASET_H
#define GENETICALGORITHM_DATASET_H

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <random>
#include <algorithm>
#include "Exceptions/DifferentSizesOfVectors.h"
using namespace std;
template <typename FeaturesType, typename LabelsType>
class Dataset{
private:
	std::vector<std::vector<FeaturesType>> vectorOfFeatures;
	std::vector<std::vector<LabelsType>> vectorOfLabels;
	std::vector<std::vector<long>> vectorOfIndexes;
public:
	Dataset(){ };

	Dataset(const std::vector<std::vector<FeaturesType>> &vectorOfFeaturesToLoad,
	        const std::vector<std::vector<LabelsType>> &vectorOfLabelsToLoad){
		if(vectorOfFeaturesToLoad.size() != vectorOfLabelsToLoad.size()){
			throw DifferentSizesOfVectors("Dataset: Features and labels vectors are not equal in length");
		}
		else{
			vectorOfFeatures = vectorOfFeaturesToLoad;
			vectorOfLabels = vectorOfLabelsToLoad;
			setVectorOfIndexes();
		}
	}

	void setVectorOfIndexes(){
		long index = 0;
		vector<long> aClassIndexes;
		vector<long> bClassIndexes;
		for(const auto &label:vectorOfLabels){
				if(label[0] == 0){
					aClassIndexes.push_back(index);
				}
				if(label[0] == 1){
					bClassIndexes.push_back(index);
				}
				index++;
			}
		vectorOfIndexes.push_back(aClassIndexes);
		vectorOfIndexes.push_back(bClassIndexes);
	};

	Dataset(const Dataset &dataset){
		vectorOfFeatures = dataset.getVectorOfFeatures();
		vectorOfLabels = dataset.getVectorOfLabels();
		vectorOfIndexes = dataset.getVectorOfIndexes();
	};

    void getSubsets(double percent_of_subset_for_training_set, double percent_of_subset_for_test_set, Dataset<FeaturesType, LabelsType> &training_set, Dataset<FeaturesType, LabelsType> &test_set)
    {
        long loop_control = 0;
        long a_class_index = 0;
        long b_class_index = 0;
        vector<vector<double>> random_features;
        vector<vector<double>> random_labels;
        vector<long> chosen_indexes;
        random_device rd;
        mt19937 rng(rd());
        uniform_int_distribution<long> a_class(this->vectorOfIndexes[0].front(), this->vectorOfIndexes[0].size());
        uniform_int_distribution<long> b_class(this->vectorOfIndexes[1].front(), this->vectorOfIndexes[1].size());
        while (loop_control < (this->vectorOfLabels.size() * percent_of_subset_for_training_set)/ 2)
        {
            a_class_index = this->vectorOfIndexes[0][a_class(rng)];
            b_class_index = this->vectorOfIndexes[1][b_class(rng)];
            if (find(chosen_indexes.begin(), chosen_indexes.end(), a_class_index) == chosen_indexes.end() && find(chosen_indexes.begin(), chosen_indexes.end(), b_class_index) == chosen_indexes.end()) {
                random_features.push_back(this->getVectorOfFeatures()[a_class_index]);
                random_labels.push_back(this->getVectorOfLabels()[a_class_index]);
                random_features.push_back(this->getVectorOfFeatures()[b_class_index]);
                random_labels.push_back(this->getVectorOfLabels()[b_class_index]);
                chosen_indexes.push_back(a_class_index);
                chosen_indexes.push_back(b_class_index);
                loop_control++;
            }
        }
        training_set.vectorOfFeatures = random_features;
        training_set.vectorOfLabels = random_labels;
	    training_set.setVectorOfIndexes();
        random_features.clear();
        random_labels.clear();
        loop_control = 0;
        while (loop_control < (this->getVectorOfLabels().size() * percent_of_subset_for_test_set) / 2)
        {
            a_class_index = this->vectorOfIndexes[0][a_class(rng)];
            b_class_index = this->vectorOfIndexes[1][b_class(rng)];
            if (find(chosen_indexes.begin(), chosen_indexes.end(), a_class_index)== chosen_indexes.end() && find(chosen_indexes.begin(), chosen_indexes.end(), b_class_index)== chosen_indexes.end()) {
                random_features.push_back(this->getVectorOfFeatures()[a_class_index]);
                random_labels.push_back(this->getVectorOfLabels()[a_class_index]);
                random_features.push_back(this->getVectorOfFeatures()[b_class_index]);
                random_labels.push_back(this->getVectorOfLabels()[b_class_index]);
                chosen_indexes.push_back(a_class_index);
                chosen_indexes.push_back(b_class_index);
                loop_control++;
            }
        }
        test_set.vectorOfFeatures = random_features;
        test_set.vectorOfLabels = random_labels;
	    test_set.setVectorOfIndexes();
        cout << "Subsets created" << endl;
        cout << "Size of training set: " << training_set.vectorOfLabels.size() << endl;
        cout << "Size of test set: " << test_set.vectorOfLabels.size() << endl;
    };

	void meanValueNormalization(double min, double max){
		vector<long> vectorOfSums;
		for(auto & feature : this->getVectorOfFeatures()[0]){
			vectorOfSums.push_back(0);
		}
		for(auto & example : this->vectorOfFeatures){
			int index = 0;
			for(auto & feature : example){
				vectorOfSums[index] =+ feature;
				index++;
			}
		}
		vector<long> vectorOfAverages;
		for(auto & sum : vectorOfSums){
			vectorOfAverages.push_back(sum/this->getLength());
		}
		for(auto & example : this->vectorOfFeatures){
			int index = 0;
			for(auto & feature : example){
				double featureNorm = (feature-vectorOfAverages[index])/(max-min);
				feature=featureNorm;
				index++;
			}
		}
	};

	const std::vector<std::vector<FeaturesType>> &getVectorOfFeatures() const{
		return vectorOfFeatures;
	};

	const std::vector<std::vector<LabelsType>> &getVectorOfLabels() const{
		return vectorOfLabels;
	};


	const std::vector<std::vector<long>> &getVectorOfIndexes() const{
		return vectorOfIndexes;
	};

	const long &getRandomAClassIndex() const{
		long randomNumber = rand() % vectorOfIndexes[0].size();
		return vectorOfIndexes[0][randomNumber];
	};

	const long &getRandomBClassIndex() const{
		long randomNumber = rand() % vectorOfIndexes[1].size();
		return vectorOfIndexes[1][randomNumber];
	};

	const long &getLength() const{
		return vectorOfLabels.size();
	}

	virtual ~Dataset(){ };

};


#endif //GENETICALGORITHM_DATASET_Hvoid Dataset::meanValueNormalization(double min, double max){

