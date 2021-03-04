/*
 * NeuronClassFunctionTest.h
 *
 *  Created on: Feb 26, 2021
 */

#include "Neuron.h"
#include <stdint.h>
#include <deque>

#ifndef SRC_NEURONCLASSFUNCTIONTEST_H_
#define SRC_NEURONCLASSFUNCTIONTEST_H_

class NeuronClassFunctionTest {

	private:
		unsigned int unique_id = 0;
		float neiWeights [2] = {0.5, 1.0};
		unsigned int neighbors [2]= {1,2};
		uint32_t numNeighbors = 2;
		deque<uint32_t>  spikeLedger [3];
		float params [12] = {-70, -20, 0.02, 0.25, -65, 6, 0.5, 0.2,0.1, 0.2, 1.1, 1.1};
		Neuron myNeuron;


	public:
		void testNeuron();
};



#endif /* SRC_NEURONCLASSFUNCTIONTEST_H_ */
