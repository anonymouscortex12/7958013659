/*
 * neuron.cpp
 *
 *  Created on: Feb 12, 2021
 */
#include <iostream>
#include <string>
#include <math.h>
#include <bitset>
#include <deque>
#include <map>
#include "Neuron.h"
using namespace std;

Neuron::Neuron(){}

Neuron::Neuron(unsigned int * unique_id, float * params, float * neiWeights, unsigned int * neighbors, uint32_t numNeighbors){
	uid = unique_id;
	//Determines neural dynamics
	v = params[0], u = params[1], a = params[2], b = params[3], \
	c = params[4], d = params[5], I = params[6], alpha = params[7], \
	A_pos = params[8], A_neg = params[9], tau_pos = params[10], tau_neg = params[11];
	weights = neiWeights;
	nei = neighbors;
	numNei = numNeighbors;
}

void Neuron::setValues(unsigned int * unique_id, float * params, float * neiWeights, unsigned int * neighbors, uint32_t numNeighbors)
{
	uid = unique_id;
		//Determines neural dynamics
		v = params[0], u = params[1], a = params[2], b = params[3], \
		c = params[4], d = params[5], I = params[6], alpha = params[7], \
		A_pos = params[8], A_neg = params[9], tau_pos = params[10], tau_neg = params[11];
		weights = neiWeights;
		nei = neighbors;
		numNei = numNeighbors;
}
void Neuron::clearSpikeHistory(deque <uint32_t> * spikeLedger) {
	//deque<uint32_t> newLedger;
	spikeLedger[*uid].clear();
}

void Neuron::updateWeights(deque <uint32_t> * spikeLedger) {
	deque <uint32_t> selfLedger = spikeLedger[*uid];
	deque <uint32_t> neiLedger;

	// These variables will be required to simulate stacks
	uint32_t p1,p2,p1_popped, p2_popped, p1_size, p2_size;
	p1_size = selfLedger.size();

	//Loop over every neighbor and update weights
	for (unsigned int i = 0; i < numNei; ++i) {
		neiLedger = spikeLedger[nei[i]];
		p2_size = neiLedger.size();
		float delta_w = 0.0;
		// Nothing to do if neighbor no spikes
		if (p2_size == 0) {
			continue;
		}
		// Get first element from selfLedger if it exists
		// Else set it to 0
		p1_popped = 0, p2_popped = 0;
		if(p1_size > 0) {
			p1 = selfLedger[p1_popped];
			p1_popped = p1_popped + 1;
		}
		else {
			p1 = 0;
		}

		while (p2_size > p2_popped) {
			p2 = neiLedger[p2_popped];

			// LTP case for current value
			if (p1 >= p2) {
				// Update weight change sum
				delta_w = delta_w + A_pos/exp((p1 - p2)/tau_pos);
				// Increment neighbor pointer
				p2_popped = p2_popped + 1;
			}

			// Check if LTD case
			else {
				// There are more spikes, possible LTD in next iteration
				if (p1_size > p1_popped) {
					p1 = selfLedger[p1_popped];
					p1_popped = p1_popped + 1;
				}
				// There are no more spikes, perform LTD and update P2
				else {
					delta_w = delta_w  - A_neg/exp((p2 - p1)/tau_neg);
					p2_popped = p2_popped + 1;
				}

			}
		}
		cout << "old_w_i:" << weights[i] << "\n";
		cout << "dw_i: " << delta_w <<"\n";
		//Update the weight
		weights[i] = weights[i] + delta_w;
		cout << weights[i] << "\n";
	}
}

void Neuron::updateLedger(deque <uint32_t> * spikeLedger, uint32_t & time) {
	//Update ledger if voltage >= 30 mV
	 if (v >= 30.0) {

		 //cout << "Updating Ledger\n";
		 spikeLedger[*uid].push_back(time);
		 //cout << "N: " << *uid << ", V: " << v << ", T: " << time << "\n";
		 v = c;
		 u = u+d;
	 }
}


void Neuron::updateVoltage(deque <uint32_t> * spikeLedger, uint32_t & time ) {
	// Check if a neighbor spiked, and update voltage accordingly.
	// While calling updateVoltage at time T, the ledger will have spike history upto time T-1.
	 float I = 0.0;
	 for (unsigned int i = 0; i < numNei; ++i) {
		 deque <uint32_t> * neiSpikes = spikeLedger + nei[i]; // access spike history using neighbor id
		 // Update I if neighbor fired
		 if (!neiSpikes->empty() and neiSpikes->back() == time - 1 ) {
				 I = I + weights[i]; // access weight for the ith neighbor
				 //cout << "Updating Volt:" << *uid << ": " << time << ": " << nei[i] << "\n";

		 }
	 }
	 //Update voltage and refactory period based on current voltage
	 float dv_dt = 0.04*pow(v, 2) + 5*v + 140 - u + I;
	 float du_dt = a*(b*v - u);
	 v = v + alpha*dv_dt;
	 u = u + alpha*du_dt;
	 //cout << "dv: " << alpha*dv_dt << ", du:" << alpha*du_dt << "\n";
	 //cout << "v: " << v << ", u:" << u << "\n";
}



