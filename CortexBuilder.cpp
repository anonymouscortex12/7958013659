/*
 * CortexBuilder.cpp
 *
 *  Created on: Mar 6, 2021
 */

#include "CortexBuilder.h"

CortexBuilder::CortexBuilder(unsigned int totalNeurons, unsigned int totalMicrocolumns, uint8_t layers, Logger * logger){
	numTotalNeurons = totalNeurons, numMicroColumns = totalMicrocolumns;
	numLayers = layers;
	if (!(numTotalNeurons % numMicroColumns == 0)) {
		logger->log("Number Columns must divide Number Neurons\n", Logger::ERROR);
		exit(EXIT_FAILURE);
	}
	numNeuronsPerColumn = numTotalNeurons / numMicroColumns;
	//Neurons for each layer =
}




/*
int random(tuple<NeuronType, >)
{
    int n = input.size();
    if (n != probability.size()) {
        return -1;        // error
    }

    // construct a sum vector from the given probabilities
    vector<int> prob_sum(n, 0);

    // `prob_sum[i]` holds sum of all `probability[j]` for `0 <= j <=i`
    prob_sum.at(0) = probability.at(0);
    for (int i = 1; i < n; i++) {
        prob_sum.at(i) = prob_sum.at(i-1) + probability.at(i);
    }

    // generate a random integer from 1 to 100 and check where it lies in `prob_sum[]`
    int r = (rand() % 100) + 1;

    // based on the comparison result, return the corresponding
    // element from the input vector

    if (r <= prob_sum.at(0)) {      // handle 0th index separately
        return input.at(0);
    }

    for (int i = 1; i < n; i++)
    {
        if (r > prob_sum.at(i-1) && r <= prob_sum.at(i)) {
            return input.at(i);
        }
    }
 */
