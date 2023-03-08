#include "LogModule.h"
#include <QDateTime>
LogModule* LogModule::m_instance = nullptr;

LogModule::LogModule()
{
	m_logFile.open("logs.txt", std::ifstream::app);
}
LogModule::~LogModule()
{
	m_logFile.close();
}

LogModule* LogModule::getInstance()
{
	if (m_instance == nullptr) {
		m_instance = new LogModule();
	}
	return m_instance;
}
void LogModule::Error(QString msg)
{
	
	msg = QDateTime::currentDateTime().toString() + " Error: " + msg;
	m_logFile.write(msg.toStdString().c_str(), msg.size());
	m_logFile << std::endl;
}
void LogModule::Info(QString msg)
{
	msg = QDateTime::currentDateTime().toString() + " Info: " + msg;
	m_logFile.write(msg.toStdString().c_str(), msg.size());
	m_logFile << std::endl;
}
