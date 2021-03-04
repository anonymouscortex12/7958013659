/*
 * NeuronSimulateTwoNodes.h
 *
 *  Created on: Feb 26, 2021
 */

#include "Neuron.h"
#include <stdlib.h>     /* srand, rand */
#include <fstream>
#include <map>
#include <iostream>

#ifndef SRC_NEURONSIMULATETWONODES_H_
#define SRC_NEURONSIMULATETWONODES_H_


class NeuronSimulateTwoNodes {
private:
	ofstream logger;
	// Types of neurons
	string neurons [13] = {"phasic_spike", "tonic_spike", "phasic_burst", "tonic_burst", \
					   "inhib_spike", "inhib_burst", "resonate", "mixed_model", \
					   "variable_thresh", "accommodate", "rebound_spike", "rebound_burst", "bistable" };
	// Map with format: {v, u, a, b, c, d, I, alpha, A_pos, A_neg, tau_pos, tau_neg}
	map <string, float *> neurolib;
	//Transformers

	float phasic_spike [12] = {-70, -20, 0.02, 0.25, -65, 6, 0.5, 0.2,0.1, 0.2, 1.1, 1.1};
	float tonic_spike [12] = {-70, -20, 0.02, 0.2, -65, 6, 14, 0.2,0.1, 0.2, 1.1, 1.1};
	float phasic_burst [12] = {-70, -20, 0.02, 0.25,-55, 0.05, 0.6, 0.2, 0.1, 0.2, 1.1, 1.1};
	float tonic_burst [12] = {-70, -20, 0.02, 0.2, -50, 2, 15, 0.2, 0.1, 0.2, 1.1, 1.1};
	float inhib_spike [12] = {-70, -20, -0.02, -1, -60, 8, 80, 0.2, 0.1, 0.2, 1.1, 1.1};
	float inhib_burst [12] = {-70, -20, -0.026, -1, -45, 0, 80, 0.2, 0.1, 0.2, 1.1, 1.1};
	float resonate [21] = {-70, -20, 0.1, 0.26, -60, -1, 0 , 0.2, 0.1, 0.2, 1.1, 1.1};
	float mixed_model [12] = {-70, -20, 0.02, 0.2, -55, 4, 10, 0.2, 0.1, 0.2, 1.1, 1.1};
	float variable_thresh [12] = {-70, -20, 0.03, 0.25,  -60, 4, 0, 0.2, 0.1, 0.2, 1.1, 1.1};
	float accommodate [12] = {-70, -20, 0.02, 1, -55, 4, 0, 0.2, 0.1, 0.2, 1.1, 1.1};
	float rebound_spike [12] = {-70, -20, 0.03, 0.25,-60, 4, 0, 0.2, 0.1, 0.2, 1.1, 1.1};
	float rebound_burst [12] = {-70, -20, 0.03, 0.25,-52, 0, 0, 0.2, 0.1, 0.2, 1.1, 1.1};
	float bistable [12] = {-70, -20, 1., 1.5,-60, 0, -65, 0.2, 0.1, 0.2, 1.1, 1.};

	//pther params
	// 0.01      0.2     -65     8        30 ;...    % spike frequency adaptation
	//    0.02      -0.1    -55     6        0  ;...    % Class 1
        // 0.2       0.26    -65     0        0  ;...    % Class 2
	// 0.02      0.2     -65     6        7  ;...    % spike latency
	// 0.05      0.26    -60     0        0  ;...    % subthreshold oscillations
	//  0.02      -0.1    -55     6        0  ;...    % integrator
public:
	NeuronSimulateTwoNodes();
	void simulateActivity(Neuron a, Neuron b, deque<uint32_t> * spikeLedger , uint32_t T);
	void simulateAndSave ();

};



#endif /* SRC_NEURONSIMULATETWONODES_H_ */
