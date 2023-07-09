#pragma once
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <thread>  
#include <mutex> 
#include <queue>
#include <time.h>


namespace utils
{
	/**
	 * Class EventLogger
	 *
	 * Log events, write into file on a separate thread.
	 */
	class EventLogger
	{
	public:
		EventLogger(const std::string &programData);
		~EventLogger();
		void setLogCondition(bool (*condition)()) { _condition = condition; };
		void addLogEvent(const std::string &log);
		const std::string& getLastLog();
	protected:
		std::string getPath();
		std::string getCurrentDateTime();
		std::string getCurrentDate();
		void logEvents();

		std::string _lastLog;
		bool (*_condition)() = nullptr;
		std::mutex _mtx;
		std::thread _thread;
		std::queue<std::string> _logs;
		bool _destruct = false;
	};
}

