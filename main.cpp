/*
 * main.cpp
 *
 *  Created on: Feb 26, 2021
 */
#include "NeuronTest.h"
#include "Logger.h"
using namespace std;

int main() {
	Logger myLog(LogLevel::DEBUG, "loggerTest.txt");
	myLog.Log("hello world",LogLevel::WARNING);
	//NeuronTest a;
	//a.testNeuron();
	return 0;
}



