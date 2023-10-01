#pragma once
#include "LoggerCls.h"
#include <string>
#include <random>


void CallTheLogger()
{
	std::string PathToLogger = "C:\\Users\\acer\\source\\repos\\LoggerForPnet\\LoggerOutPut\\Logger.txt";
	std::string Msg = " Compilation Done! ";
	int sessionNumber = 0;
	FileLogger AnyLogger(PathToLogger, Msg, sessionNumber);
	AnyLogger.WriteInConsoleLog();
	AnyLogger.WriteIpAndPortInConsole();

	AnyLogger.WriteInFileLog();
	AnyLogger.WriteIpAndPortFileLog();

	//logger.WriteInLog();
}