/*
 * Neuron.h
 *
 *  Created on: Feb 26, 2021
 */

#include <deque>
#include <stdint.h>

#ifndef SRC_NEURON_H_
#define SRC_NEURON_H_

using namespace std;

class Neuron {

	private:
	unsigned int * uid, * cid, * lid; // neuron_id, minicolumn id, layer id

	float * weights; // weights of incoming synapses; order neighbor weights and ids must be the same
	float v, u, a, b, c, d, I, alpha, A_pos, A_neg, tau_pos, tau_neg;
	unsigned int * nei; // pointer to array containing neighbor ids
	uint32_t numNei; // number neighbors to traverse arrays


	public:
	Neuron();
	Neuron(unsigned int * unique_id, unsigned int * column_id, unsigned int * layer_id, float * params, float * neiWeights, unsigned int * neighbors, uint32_t numNeighbors);
	void setValues(unsigned int * unique_id, unsigned int * column_id, unsigned int * layer_id,float * params, float * neiWeights, unsigned int * neighbors, uint32_t numNeighbors);
	void clearSpikeHistory(deque <uint32_t> * spikeLedger);
	void updateWeights(deque <uint32_t> * spikeLedger);
	void updateLedger(deque <uint32_t> * spikeLedger, uint32_t & time);
	void updateVoltage(deque <uint32_t> * spikeLedger, uint32_t & time );


};


#endif /* SRC_NEURON_H_ */
