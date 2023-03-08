#include "OutputModule.h"
#include "LogModule.h"
OutputModule* OutputModule::m_instance = nullptr;


OutputModule::OutputModule()
{
}

OutputModule* OutputModule::getInstance()
{
	if (m_instance == nullptr) {
		m_instance = new OutputModule();
	}
	return m_instance;
}
OutputModule::~OutputModule()
{
}
void OutputModule::SaveImage(cv::Mat OutputImage, QString Path)
{
	cv::imwrite(Path.toStdString(), OutputImage);
	LogModule::getInstance()->Info("File has been saved");
}
