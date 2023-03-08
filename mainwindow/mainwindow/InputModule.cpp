// This module handles all the values inputted by the user and sends them to their respective module
#include "InputModule.h"
#include "UIController.h"
#include "LogModule.h"
#include "ui_mainwindow.h"
#include <QCameraInfo>
#include <QMessageBox>
InputModule* InputModule::m_instance = nullptr;

// This sets the default values for each filter or parameter
InputModule::InputModule() :
	m_ContrastPosition(100),
	m_BrightnessPosition(0),
	m_grayEnabled(true),
	m_selectedFilter("Choose"),
	m_camera(nullptr),
	m_setContrast(100),
	m_CannyMax(200),
	m_CannyMin(100),
	m_Delta(0.0),
	m_Scale(1.0),
	m_Kernelsize(3)
{
}

InputModule::~InputModule()
{
}
InputModule* InputModule::getInstance()
{
	if (m_instance == nullptr) {
		m_instance = new InputModule();
	}
	return m_instance;
}
// This function takes the file path then opens the image file and saves it to a variable
void InputModule::setImageFilename(QString filename)
{
	m_filename = filename;
	m_image = cv::imread(filename.toStdString());
	// This tells the log module that it should the print a message
	LogModule::getInstance()->Info("File has been loaded successfully ");
}
// This function only returns loaded images to other modules
cv::Mat InputModule::getImage()
{
	return m_image;
}
// This function stores the position of the contrast slider which is set by the user and stores it in a variable
void InputModule::setContrast(int position)
{
	m_ContrastPosition = position;
	// This tells the log module that is should print the message
	LogModule::getInstance()->Info("Contrast has been set to " + QString::number(position));
}
// This function returns the contrast value to other variables
int InputModule::getContrast()
{
	return m_ContrastPosition;
}
// This function stores the position of the brightness slider which is set by the user and stores it in a variable
void InputModule::setBrightness(int position)
{
	m_BrightnessPosition = position;
	// This tells the log module that is should print the message
	LogModule::getInstance()->Info("Brightness has been set to " + QString::number(position));
}
// This function returns the brightness value to other variables
int InputModule::getBrightness()
{
	return m_BrightnessPosition;
}
// This function checks if the check box is checked which is controlled by the user and stores it in a variable
void InputModule::enableGray(bool value)
{
	m_grayEnabled = value;
	// If the grayscale check box is checked 
	if (m_grayEnabled == true) {
		// This tells the log module that is should print the message
		LogModule::getInstance()->Info("Grayscale conversion has been enabled ");
	}
	// If the grayscale check box is not checked 
	else {
		// This tells the log module that is should print the message
		LogModule::getInstance()->Info("Grayscale conversion has been disabled ");
	}
}
// This function returns to other modules if grayscale is enabled or disabled
bool InputModule::isGrayEnabled()
{
	return m_grayEnabled;
}
// This function checks which edge detction method was chosen by the user and sets the value in a variable
void InputModule::setFilter(QString filter)
{
	m_selectedFilter = filter;
	// This tells the log module that is should print the message
	LogModule::getInstance()->Info(filter + " Has been applied");
}
// This function returns to other modules what edge detection method was chosen
QString InputModule::getFilter()
{
	return m_selectedFilter;
}
// This function loads the first available camera and provides the frames to the output display window
void InputModule::setInputAsCamera(QCameraViewfinder *viewfinder)
{
	// Looks for the available cameras
	const QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
	// If no cameras were found then print log message
	if (cameras.size() == 0) {
		// Creates a pop box with an error message to inform the user that no camera is connected
		QMessageBox::information(NULL, QString ("Error"), QString("No Camera is Connected"), QMessageBox::Ok, 0);
		// This tells the log module that is should print the message
		LogModule::getInstance()->Error("Camera is not available ");

	}
	// If camera was found
	else {
		for (const QCameraInfo &cameraInfo : cameras) {
			// Stores the camera's name
			QString  deviceName = cameraInfo.deviceName();
			// This tells the log module that is should print the message
			LogModule::getInstance()->Info("Camera " + deviceName + " has been enabled ");
			//if (cameraInfo.deviceName() == "mycamera")
			m_camera = new QCamera(cameraInfo); // creates a frame
			m_camera->setViewfinder(viewfinder); // display the camera image
			m_camera->start(); // starts the camera
		}
	}
}
void InputModule::setInputAsImage()
{
	if (m_camera != nullptr)
	{
		m_camera->stop(); // stops the camera
	}
	LogModule::getInstance()->Info("File input mode had been enabled ");
}
void InputModule::setCannyMax(int value)
{
	m_CannyMax = value;
	LogModule::getInstance()->Info("Canny Maximum has been set to " + QString::number(value));
}
int InputModule::getCannyMax()
{
	return m_CannyMax;
}
void InputModule::setCannyMin(int value)
{
	m_CannyMin = value;
	LogModule::getInstance()->Info("Canny Minimum has been set to " + QString::number(value));
}
int InputModule::getCannyMin()
{
	return m_CannyMin;
}
void InputModule::setDelta(double value)
{
	m_Delta = value;
	LogModule::getInstance()->Info("Delta value has been changed to " + QString::number(value));
}
double InputModule::getDelta()
{
	return m_Delta;
}
void InputModule::setScale(double value)
{
	m_Scale = value;
	LogModule::getInstance()->Info("Scale value has been changed to " + QString::number(value));
}
double InputModule::getScale()
{
	return m_Scale;
}
void InputModule::setKernel(int value)
{
	m_Kernelsize = value;
	LogModule::getInstance()->Info("Kernel value has been changed to " + QString::number(value));
}
int InputModule::getKernel()
{
	return m_Kernelsize;
}



