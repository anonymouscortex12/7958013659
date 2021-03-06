/*
 * Logger.h
 *
 *  Created on: Mar 6, 2021
 */


#ifndef SRC_LOGGER_H_
#define SRC_LOGGER_H_

#include <string>
#include <fstream>

using namespace std;

enum LogLevel {ERROR, WARNING, INFO, DEBUG};

class Logger
{

private:
	LogLevel loggerLevel;
	ofstream logFile;

public:
    Logger(LogLevel level, const char * filePath);
    ~Logger();
    void Log(const char * message, LogLevel messageLevel);
};

#endif /* SRC_LOGGER_H_ */
