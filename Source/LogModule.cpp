// This module takes the information or error messages from other modules and 
// puts the date and time to the message and saves into a text file named "logs.txt"
#include "LogModule.h"
#include <QDateTime>
// instance of the class
LogModule* LogModule::m_instance = nullptr;

// Constructor
LogModule::LogModule()
{
	// Create a text file and opens it for other functions to write in it
	m_logFile.open("logs.txt", std::ifstream::app);
}
// Destructor
LogModule::~LogModule()
{
	// closes the file so it can't be edited
	m_logFile.close();
}

// This function enables other modules to be able to call function in this module
LogModule* LogModule::getInstance()
{
	// if the instance is not initialized
	if (m_instance == nullptr) {
		// initialize once and carries the object of the class
		m_instance = new LogModule();
	}
	// returns the object of the class
	return m_instance;
}
// This module takes the error message from other modules and puts in the log text file
void LogModule::Error(QString msg)
{
	// This variable stores the time, date and error message 
	msg = QDateTime::currentDateTime().toString() + " Error: " + msg;
	// This writes the error message into the text file
	m_logFile.write(msg.toStdString().c_str(), msg.size());
	// This creates a new line for new messages
	m_logFile << std::endl;
}
// This takes an information message from other modules and puts it in the log text file
void LogModule::Info(QString msg)
{
	// This variable stores the time, date and information message
	msg = QDateTime::currentDateTime().toString() + " Info: " + msg;
	// This writes the information message into the text file
	m_logFile.write(msg.toStdString().c_str(), msg.size());
	// This creates a new line for any new message
	m_logFile << std::endl;
}
