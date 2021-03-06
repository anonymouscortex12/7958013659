/*
 * CortexBuilder.h
 *
 *  Created on: Mar 6, 2021
 */

#ifndef SRC_CORTEXBUILDER_H_
#define SRC_CORTEXBUILDER_H_

#include <map>
#include <vector>
#include "Logger.h"
using namespace std;


class CortexBuilder {

public:
	enum NeuronType {PHASIC_SPIKE, TONIC_SPIKE, PHASIC_BURST, TONIC_BURST,  \
						INHIBITORY_SPIKE, INHIBITORY_BURST, RESONATE, MIXED_MODE, \
						VARIABLE_THRESH, ACCOMODATE, REBOUND_SPIKE, REBOUND_BURST, \
						BISTABLE, ADAPTATION, CLASS_1, CLASS_2, LATENCY, SUB_THRESH, \
						INTEGRATOR, FIRST = PHASIC_SPIKE, LAST = INTEGRATOR};
	CortexBuilder();
	CortexBuilder(uint8_t layers, Logger * log);

private:
	//CORTEX-TREE
	uint8_t numLevelsCortexTree, numColumnsTopLevel;

	//numHubsLevelX = numHubsPerBlockByLevel[LevelX]
	vector<uint8_t> numHubsPerBlockByLevel;

	//numColumnsLevelX = (numColumnsLevelXMinus1 / numHubsPerBlockLevelXMinus1 ) * numColumnsPerBlockByLevel[LevelXMinus1]
	vector<uint8_t> numColumnsPerBlockByLevel;

	//numConnectionsSingleNeuronColumnAToAllNeuronsColumnBLevelX = numNeuronsColumnBLevelX * interColConnProbByLevel[LevelX]
	vector<float> interColConnProbByLevel; // We may need to modify this to include connectivity design by level

	//MICROCOLUMNS
	unsigned int numNeuronsPerColumn;
	uint8_t numLayersPerColumn;
	// numNueronsLayerX = neuronDistribByLayer[LayerX]*numNeuronsPerColumn
	float * neuronDistribByLayer;
	// numNeuronsLayerXNeuronTypeY = numNueronsLayerX*neuronProbByLayer[LayerX][NeuronTypeY]
	vector<float *> neuronProbByLayer;
	// numConnLayerXToLayerY = numNeuronsLayerX * (intraSynapticConnProbByLayer[LayerX][LayerY])
	vector<float *> intraSynapticConnProbByLayer;
	map<NeuronType, vector <float> > neuronParamsByType = {
								{PHASIC_SPIKE,  {-70, -20, 0.02, 0.25, -65, 6, 0.5}},
								{TONIC_SPIKE, {-70, -20, 0.02, 0.2, -65, 6, 14}},
								{PHASIC_BURST, {-70, -20, 0.02, 0.25,-55, 0.05, 0.6}},
								{TONIC_BURST, {-70, -20, 0.02, 0.2, -50, 2, 15}},
								{INHIBITORY_SPIKE, {-70, -20, -0.02, -1, -60, 8, 80}},
								{INHIBITORY_BURST, {-70, -20, -0.026, -1, -45, 0, 80}},
								{RESONATE, {-70, -20, 0.1, 0.26, -60, -1, 0}},
								{MIXED_MODE, {-70, -20, 0.02, 0.2, -55, 4, 10}},
								{VARIABLE_THRESH, {-70, -20, 0.03, 0.25,  -60, 4, 0}},
								{ACCOMODATE, {-70, -20, 0.02, 1, -55, 4, 0}},
								{REBOUND_SPIKE, {-70, -20, 0.03, 0.25,-60, 4, 0}},
								{REBOUND_BURST, {-70, -20, 0.03, 0.25,-52, 0, 0}},
								{BISTABLE,  {-70, -20, 1., 1.5,-60, 0, -65}},
								{ADAPTATION, {-70, -20,0.01, 0.2, -65, 8, 30}},
								{CLASS_1,{-70, -20,0.02, -0.1,-55, 6, 0}},
								{CLASS_2, {-70, -20,0.2 ,0.26,-65 , 0, 0}},
								{LATENCY, {-70, -20,0.02,0.2,-65 ,6 ,7}},
								{SUB_THRESH, {-70, -20,0.05, 0.26,-60,0,0}},
								{INTEGRATOR, {-70, -20, 0.02,-0.1,-55,6,0}},
					};

};



#endif /* SRC_CORTEXBUILDER_H_ */
