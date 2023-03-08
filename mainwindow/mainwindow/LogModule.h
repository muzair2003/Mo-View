#pragma once
#include <iostream> 
#include <fstream>
#include<QString>
class LogModule
{
public:
	static LogModule* getInstance();
	static LogModule* m_instance;
	void Error(QString msg);
	void Info(QString msg);
	LogModule();
	~LogModule();
private:
	std::ofstream m_logFile;
};

