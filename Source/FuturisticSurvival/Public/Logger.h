// developed by Neko

#pragma once

#include <string>
#include <Windows.h>
#include <fstream>
#include <chrono>
#include <iostream>

#define LOGREFACE "\\SurvLog_"

enum ERRORLEVEL
{
	EL_DEBUG = 0,
	EL_WARNING = 1,
	EL_ERROR = 2,
	EL_CRITICAL = 3
};

class Logger
{
private:

	static Logger* pInstance;

	std::string Path()
	{
		std::string Ret;
		char ExecPath[FILENAME_MAX];
		GetCurrentDirectoryA(sizeof(ExecPath), ExecPath);
		Ret = ExecPath;
		Ret += LOGREFACE;
		Ret += TodayDateAsString();
		Ret += ".txt";
		return Ret;
	}

#pragma warning(disable:4996)

	std::string TodayDateAsString()
	{
		std::string ret;
		time_t Now;
		time(&Now);

		struct tm* pTime;
		pTime = std::localtime(&Now);
		ret += int2string(pTime->tm_year + 1900);
		ret += "-";
		ret += int2string(pTime->tm_mon + 1);
		ret += "-";
		ret += int2string(pTime->tm_mday);
		return ret;
	}

	std::string GetCurrentTimeStamp()
	{
		std::string ret;
		time_t Now;
		time(&Now);
		struct tm* pTime;
		pTime = std::localtime(&Now);

		ret = int2string(pTime->tm_hour);
		ret += ":";
		ret += int2string(pTime->tm_min);
		ret += ":";
		ret += int2string(pTime->tm_sec);
		return ret;
	}

#pragma warning(default:4996)

	std::string int2string(const int& i, bool padded = true)
	{
		std::ostringstream format_message;
		format_message << i;
		std:: string ret = format_message.str();
		if (padded && ret.length() == 1)
		{
			ret = "0" + ret;
		}
		return ret;
	}

	std::string ErrorLevelAsString(ERRORLEVEL level)
	{
		switch (level)
		{
			case ERRORLEVEL::EL_DEBUG:
			return "[DEBUGGING] ";
			case ERRORLEVEL::EL_WARNING:
			return "[WARNING] ";
			case ERRORLEVEL::EL_ERROR:
			return "[*ERROR*] ";
			case ERRORLEVEL::EL_CRITICAL:
			return "[!!!CRITICAL ERROR!!!] ";
			default:
			return "UNKNOWN ERROR LEVEL ";
		}
	}

public:

	static Logger* GetInstance()
	{
		if (!pInstance)
		{
			
		}
		return pInstance;	
	}

	void AddMessage(std::string Msg, ERRORLEVEL level)
	{
		std::string LogLine;
		LogLine += TodayDateAsString();
		LogLine += " ";
		LogLine += GetCurrentTimeStamp();
		LogLine += ": ";
		LogLine += Msg;
		LogLine += "\n";
		std::ofstream fout;
		std::string path = Path();
		fout.open(path, std::ios_base::app);
		fout << LogLine;
		fout.close();
	}
};
