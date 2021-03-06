/*
 * NeuronSimulateTwoNodes.cpp
 *
 *  Created on: Feb 26, 2021
 */

#include "NeuronSimulateTwoNodes.h"

NeuronSimulateTwoNodes::NeuronSimulateTwoNodes() {

	//Initialize map
	neurolib["phasic_spike"] = phasic_spike;
	neurolib["tonic_spike"] = tonic_spike;
	neurolib["phasic_burst"] = phasic_burst;
	neurolib["tonic_burst"] = tonic_burst;
	neurolib["inhib_spike"] = inhib_spike;
	neurolib["inhib_burst"] = inhib_burst;
	neurolib["resonate"]= resonate;
	neurolib["mixed_model"]= mixed_model;
	neurolib["variable_thresh"] = variable_thresh;
	neurolib["accommodate"] = accommodate;
	neurolib["rebound_spike"] = rebound_spike;
	neurolib["rebound_burst"] = rebound_burst;
	neurolib["bistable"]= bistable;
}

void NeuronSimulateTwoNodes::simulateActivity(Neuron a, Neuron b, deque<uint32_t> * spikeLedger , uint32_t T) {

	// Add input current
	spikeLedger[0].push_back(0);
	spikeLedger[1].push_back(0);
	for (uint32_t i = 1; i <= T; ++i) {

		a.updateVoltage(spikeLedger, i);
		b.updateVoltage(spikeLedger, i);
		a.updateLedger(spikeLedger, i);
		b.updateLedger(spikeLedger, i);
		// Add input current with 70% probability
		if (rand() % 10 > 2) {
			spikeLedger[0].push_back(i);
		}
		if (rand() % 10 > 2) {
			spikeLedger[1].push_back(i);
		}
	}
	logger << "\nBegin LedgerHistory for N_1 \n[";
	if (spikeLedger[2].size() > 0) {
	for (unsigned int i = 0; i < spikeLedger[2].size(); ++i) {
		logger << spikeLedger[2].at(i) << ",";
	}
	}
	logger << "]\n";
	logger << "Begin LedgerHistory for N_2 \n[";
	if (spikeLedger[3].size() > 0) {
		for (unsigned int i = 0; i < spikeLedger[3].size(); ++i) {
			logger << spikeLedger[3].at(i) << ",";
		}
	}
	logger << "]\n\n";
	a.clearSpikeHistory(spikeLedger);
	b.clearSpikeHistory(spikeLedger);
}

void NeuronSimulateTwoNodes::simulateAndSave () {
	logger.open("SIM_2N_10000T.txt");
	deque<uint32_t> spikeLedger [4];
	unsigned int cid_lid = 0;
	unsigned int n_1_id = 2;
	unsigned int n_2_id = 3;
	unsigned int neighbors_1[2] = {0, n_2_id};
	unsigned int neighbors_2[2] = {1, n_1_id};
	float neiWeights_1 [2];
	float neiWeights_2 [2];

	uint32_t simulationSteps = 10000;

	for (unsigned int i = 0; i< 13; ++i) {
		for (unsigned int j = 0; j < 13; ++j) {
			logger << "\n\n\n--------------------- STARTING NEW SIMULATION ---------------------\n";
			logger << "N_1: " << neurons[i] << "; N_2: " << neurons[j] << "\n";

			Neuron n_1(&n_1_id, &cid_lid, &cid_lid, neurolib[neurons[i]], neiWeights_1,neighbors_1, 2);
			Neuron n_2(&n_2_id, &cid_lid, &cid_lid, neurolib[neurons[j]], neiWeights_2, neighbors_2, 2);
			// I_1 -> n_1 -> n_2, excite
			logger << "\n\nCircuit:  I_1 -> n_1 -> n_2, excite \n";
			neiWeights_1[0] = 5.0, neiWeights_1[1] = 0.0;
			neiWeights_2[0] = 0.0, neiWeights_2[1] = 5.0;

			NeuronSimulateTwoNodes::simulateActivity(n_1, n_2, spikeLedger, simulationSteps);

			// I_1 -> n_1 -> n_2, inhib
			logger << "Circuit: I_1 -> n_1 -> n_2, inhib \n";
			neiWeights_1[0] = 5.0, neiWeights_1[1] = 0.0;
			neiWeights_2[0] = 0.0, neiWeights_2[1] = -5.0;
			NeuronSimulateTwoNodes::simulateActivity(n_1, n_2, spikeLedger, simulationSteps);
			// I_1 -> n_1 -> n_2 <- I_2, excite
			logger << "Circuit: I_1 -> n_1 -> n_2 <- I_2, excite \n";
			neiWeights_1[0] = 5.0, neiWeights_1[1] = 0.0;
			neiWeights_2[0] = 5.0, neiWeights_2[1] = 5.0;
			NeuronSimulateTwoNodes::simulateActivity(n_1, n_2, spikeLedger, simulationSteps);
			// I_1 -> n_1 -> n_2 <- I_2, inhib
			logger << "Circuit: I_1 -> n_1 -> n_2 <- I_2, inhib \n";
			neiWeights_1[0] = 5.0, neiWeights_1[1] = 0.0;
			neiWeights_2[0] = 5.0, neiWeights_2[1] = -5.0;
			NeuronSimulateTwoNodes::simulateActivity(n_1, n_2, spikeLedger, simulationSteps);
			// I_1 -> n_1 -> <- n_2 <- I_2, excite, excite (repeated)
			logger << "Circuit:  I_1 -> n_1 -> <- n_2 <- I_2, excite, excite (repeated) \n";
			neiWeights_1[0] = 5.0, neiWeights_1[1] = 5.0;
			neiWeights_2[0] = 5.0, neiWeights_2[1] = 5.0;
			NeuronSimulateTwoNodes::simulateActivity(n_1, n_2, spikeLedger, simulationSteps);
			// I_1 -> n_1 -> <- n_2 <- I_2, inhibit, excite
			logger << "Circuit:   I_1 -> n_1 -> <- n_2 <- I_2, inhibit, excite \n";
			neiWeights_1[0] = 5.0, neiWeights_1[1] = -5.0;
			neiWeights_2[0] = 5.0, neiWeights_2[1] = 5.0;
			NeuronSimulateTwoNodes::simulateActivity(n_1, n_2, spikeLedger, simulationSteps);
			// I_1 -> n_1 -> <- n_2 <- I_2, inhibit, inhibit (repeated)
			logger << "Circuit:  I_1 -> n_1 -> <- n_2 <- I_2, inhibit, inhibit (repeated) \n";
			neiWeights_1[0] = 5.0, neiWeights_1[1] = -5.0;
			neiWeights_2[0] = 5.0, neiWeights_2[1] = -5.0;
			NeuronSimulateTwoNodes::simulateActivity(n_1, n_2, spikeLedger, simulationSteps);

		}

	}

	logger.close();
	cout << "DONE";

}




