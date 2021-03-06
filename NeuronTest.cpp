/*
 * NeuronTest.cpp
 *
 *  Created on: Feb 26, 2021
 */
#include "Neuron.h"
#include "NeuronTest.h"
using namespace std;

void NeuronTest::testNeuron()  {
	myNeuron.setValues(&unique_id, &column_id, &layer_id,params, neiWeights, neighbors, numNeighbors);
	//Test for updating voltage
	for (uint32_t i = 0; i< 10; ++i) {
		spikeLedger[1].push_back(i);
		spikeLedger[2].push_back(i);
		myNeuron.updateVoltage(spikeLedger, i);
		myNeuron.updateLedger(spikeLedger, i);
	}

	//Test for updating weights
	myNeuron.updateWeights(spikeLedger);


	//Test for clearing history
	myNeuron.clearSpikeHistory(spikeLedger);

}
