#pragma once
#pragma warning(disable : 4996)
#include <boost/asio.hpp>
#include <fstream>
#include <string>
#include <iostream>
#include <filesystem>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <time.h>


class ConsoleLogger
{
public:
	ConsoleLogger(const std::string& strPath, const std::string& strMsg, int sessionNum)
		: m_strPath(strPath),
		m_strMsg(strMsg),
		m_intSessNumber(sessionNum)
	{
		std::cout << "| INFO > " << "Constructor class LogCreator created. " << " Address #" << "[this=" << this << "]" << " Line #" << __LINE__ << std::endl;
	}	
	//sdasdadasd
	void WriteInConsoleLog()
	{
		std::time_t time = std::time({});
		char timeString[std::size("yyyy-mm-ddThh:mm:ssZ")];
		std::strftime(std::data(timeString), std::size(timeString),
			"%FT%TZ", std::gmtime(&time));		
		auto nameFile = std::filesystem::path(m_strPath);
		std::cout << "| INFO > " << "File Path #" << m_strPath << " File Name #" << nameFile.filename() << " Line # " << __LINE__ << std::endl;
		std::cout << "| INFO>" << " Session Number #" << m_intSessNumber << " Message: " << m_strMsg << " Time: " << timeString << " Line # " << __LINE__ << std::endl;
	}

	void WriteIpAndPortInConsole()
	{
		using boost::asio::ip::tcp;
		boost::asio::io_service io_service;
		tcp::resolver resolver(io_service);
		tcp::resolver::query query(boost::asio::ip::host_name(), "");
		tcp::resolver::iterator iter = resolver.resolve(query);
		tcp::resolver::iterator end; // End marker.
		while (iter != end)
		{
			tcp::endpoint ep = *iter++;
			std::cout <<"| INFO > "<< "Allow address and port: " << ep << " Line# "<< __LINE__ << std::endl;
		}
	}
	std::string getStrPath() { return m_strPath; }
	std::string getStrMsg() { return m_strMsg; }
	int getSessionNumber() { return m_intSessNumber; }

	 ~ConsoleLogger() { std::cout  << "| INFO > " << "Destroying #" << " [this=" << this << "] " << " Line # " << __LINE__ << std::endl; }

	 int operator ++()
	 {
		 return m_intSessNumber++;
	 }

private:
	std::string m_strPath;
	std::string m_strMsg;
	int m_intSessNumber;
	//::ofstream m_streamFileLog;
};


class FileLogger :public ConsoleLogger
{
public:
	FileLogger(const std::string& strPath, const std::string& strMsg, int sessionNum)
		:ConsoleLogger(strPath, strMsg, sessionNum),m_logFile(strPath)
	{
		auto nameFile = std::filesystem::path(getStrPath());
		if (!m_logFile.is_open())
		{
			std::cerr << "error with openning file! " << nameFile.filename() << "line: #" << __LINE__ << std::endl;
		}
		m_logFile << "| INFO > " << "Constructor class LogCreator created. " << " Address #" << "[this=" << this << "]" << " Line #" << __LINE__ << std::endl;
	
	}
	
	void WriteInFileLog()
	{
		std::time_t time = std::time({});
		char timeString[std::size("yyyy-mm-ddThh:mm:ssZ")];
		std::strftime(std::data(timeString), std::size(timeString),
			"%FT%TZ", std::gmtime(&time));
		auto nameFile = std::filesystem::path(getStrPath());
		m_logFile << "| INFO > " << "File Path #" << getStrPath() << " File Name #" << nameFile.filename() << " Line # " << __LINE__ << std::endl;
		m_logFile << "| INFO>" << " Session Number #" << getSessionNumber() << " Message: " << getStrMsg() << " Time: " << timeString << " Line # " << __LINE__ << std::endl;
	}

	void WriteIpAndPortFileLog()
	{
		using boost::asio::ip::tcp;
		boost::asio::io_service io_service;
		tcp::resolver resolver(io_service);
		tcp::resolver::query query(boost::asio::ip::host_name(), "");
		tcp::resolver::iterator iter = resolver.resolve(query);
		tcp::resolver::iterator end; // End marker.
		while (iter != end)
		{
			tcp::endpoint ep = *iter++;
			m_logFile << "| INFO > " << "Allow address and port: " << ep << " Line# " << __LINE__ << std::endl;
		}
	}
	~FileLogger() { m_logFile << "| INFO > " << "Deleting object  #" << "[" << this << "]" << " Line#" << __LINE__ << std::endl; }


private:
	std::ofstream m_logFile;
};







