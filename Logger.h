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



class Logger
{

public:
	enum LogLevel {ERROR, WARNING, INFO, DEBUG};
    Logger(LogLevel level, const char * filePath);
    ~Logger();
    void log(const char * message, LogLevel messageLevel);

private:
	LogLevel loggerLevel;
	ofstream logFile;

};

#endif /* SRC_LOGGER_H_ */
