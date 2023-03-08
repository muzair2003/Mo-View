#pragma once
#include "opencv2\core.hpp"
#include <QString>
#include "opencv2\imgcodecs.hpp"
class OutputModule
{
public:
	OutputModule();
	~OutputModule();
	static OutputModule* getInstance();
	static OutputModule* m_instance;
	void SaveImage(cv::Mat OutputImage, QString Path);
};

