/*
 * main.cpp
 *
 *  Created on: Feb 26, 2021
 */
#include "NeuronTest.h"
#include "Logger.h"
using namespace std;

int main() {
	Logger myLog(Logger::DEBUG, "loggerTest.txt");
	myLog.log("hello world",Logger::WARNING);
	//NeuronTest a;
	//a.testNeuron();
	return 0;
}



