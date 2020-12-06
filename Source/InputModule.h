#pragma once
#include <QString>
#include "opencv2\core.hpp"
#include "opencv2\imgcodecs.hpp"
#include <QCameraViewfinder>

class InputModule
{
public:
	InputModule();
	~InputModule();
	static InputModule* getInstance();
	void setImageFilename(QString filename);
	QString getImageFilename();
	cv::Mat getImage();
	void setContrast(int position);
	void setBrightness(int position);
	int getContrast();
	int getBrightness();
	bool isGrayEnabled();
	void enableGray(bool value);
	static InputModule* m_instance;
	void setFilter(QString filter);
	QString getFilter();
	bool setInputAsCamera(QCameraViewfinder *viewfinder);
	void setInputAsImage();
	void setCannyMax(int value);
	void setCannyMin(int value);
	int getCannyMax();
	int getCannyMin();
	void setDelta(double value);
	double getDelta();
	void setScale(double value);
	double getScale();
	void setKernel(int value);
	int getKernel();
private:
	QCamera *m_camera;
	QString m_filename;
	int m_ContrastPosition;
	int m_BrightnessPosition;
	int m_setContrast;
	bool m_grayEnabled;
	QString m_selectedFilter;
	cv::Mat m_image;
	QString m_savefilename;
	int m_CannyMax;
	int m_CannyMin;
	double m_Delta;
	double m_Scale;
	int m_Kernelsize;

};

