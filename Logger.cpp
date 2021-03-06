/*
 * Logger.cpp
 *
 *  Created on: Mar 6, 2021
 */

#include "Logger.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <string.h>

using namespace std;

Logger::Logger(LogLevel level, const char * filePath) {
	loggerLevel = level;
	logFile.open(filePath);
	if (!logFile.is_open()) {
		cout << "ERROR: Could not open log file";
	}
}

Logger::~Logger() {
	if (logFile.is_open()) {
		logFile.close();
	}
}

void Logger::Log(const char * message, LogLevel messageLevel) {
	if (loggerLevel >= messageLevel ) {
		time_t c_time = chrono::system_clock::to_time_t(chrono::system_clock::now());
		char * c_time_char = ctime(&c_time);
		c_time_char[strlen(c_time_char) - 1] = '\0';
		logFile << "[" << c_time_char << "]: " << message << "\n";
	}
}

