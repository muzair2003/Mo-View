// This module stores all the values inputted by the user through the UI and provides them to other modules
// this is mainly composed of getters and setters of all the user input data
#include "InputModule.h"
#include "UIController.h"
#include "LogModule.h"
#include "ui_moView.h"
#include <QCameraInfo>
#include <QMessageBox>
// instance of the class
InputModule* InputModule::m_instance = nullptr;
// Constructor
InputModule::InputModule() :
	// This sets the default values for each user input data
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
// Destructor
InputModule::~InputModule()
{
	// If the camera has been started
	if (m_camera != nullptr)
	{
		// Stops the camera
		m_camera->stop();
		// deletes the camera variable to prevent memory leaks
		delete m_camera;
	}
}
// This function enables other modules to be able to call function in this module
InputModule* InputModule::getInstance()
{
	// if the instance is not initialized
	if (m_instance == nullptr) {
		// initialize once and carries the object of the class
		m_instance = new InputModule();
	}
	// returns the object of the class
	return m_instance;
}
// This function takes the file path then loads the image file and saves it to a variable
void InputModule::setImageFilename(QString filename)
{
	// This variable stores the file path
	m_filename = filename;
	// Stores the image data in a variable
	m_image = cv::imread(filename.toStdString());
	// This tells the log module that it should the print a message
	LogModule::getInstance()->Info("File has been loaded successfully ");
}
// this function provides the file path of the image
QString InputModule::getImageFilename()
{
	// returns the file path
	return m_filename;
}
// This function only returns loaded images to other modules
cv::Mat InputModule::getImage()
{
	// This returns the image file to other modules
	return m_image;
}
// This function stores the position of the contrast slider which is set by the user and stores it in a variable
void InputModule::setContrast(int position)
{
	// This variable stores the value
	m_ContrastPosition = position;
	// This tells the log module that is should print the message
	LogModule::getInstance()->Info("Contrast has been set to " + QString::number(position / 100.0));
}
// This function returns the contrast value to other modules
int InputModule::getContrast()
{
	// This variable stores the value
	return m_ContrastPosition;
}
// This function stores the position of the brightness slider which is set by the user and stores it in a variable
void InputModule::setBrightness(int position)
{
	// This variable stores the value
	m_BrightnessPosition = position;
	// This tells the log module that is should print the message
	LogModule::getInstance()->Info("Brightness has been set to " + QString::number(position));
}
// This function returns the brightness value to other variables
int InputModule::getBrightness()
{
	// This returns the brightness value to other modules
	return m_BrightnessPosition;
}
// This function checks if the check box is checked which is controlled by the user and stores it in a variable
void InputModule::enableGray(bool value)
{
	// This variable stores the value
	m_grayEnabled = value;
	// If the gray scale check box is checked 
	if (m_grayEnabled == true) {
		// This tells the log module that is should print the message
		LogModule::getInstance()->Info("Gray scale conversion has been enabled ");
	}
	// If the gray scale check box is not checked 
	else {
		// This tells the log module that is should print the message
		LogModule::getInstance()->Info("Gray scale conversion has been disabled ");
	}
}
// This function returns to other modules if gray scale is enabled or disabled
bool InputModule::isGrayEnabled()
{
	// This returns the if gray scale is enabled or disabled to other modules
	return m_grayEnabled;
}
// This function checks which edge detection method was chosen by the user and sets the value in a variable
void InputModule::setFilter(QString filter)
{
	// This variable stores the value
	m_selectedFilter = filter;
	// This tells the log module that is should print the message
	LogModule::getInstance()->Info(filter + " Has been applied");
}
// This function returns to other modules what edge detection method was chosen
QString InputModule::getFilter()
{
	// This returns the selected filter to other modules
	return m_selectedFilter;
}
// This function stores the maximum threshold of the canny filter set by the user in an variable
void InputModule::setCannyMax(int value)
{
	// This stores the maximum threshold value
	m_CannyMax = value;
	// This tells the log module that is should print the message
	LogModule::getInstance()->Info("Canny Maximum has been set to " + QString::number(value));
}
// This function returns to other modules the maximum threshold of the canny filter
int InputModule::getCannyMax()
{
	// This returns the maximum threshold value to other modules
	return m_CannyMax;
}
// This function stores the minimum threshold of the canny filter set by the user in an variable
void InputModule::setCannyMin(int value)
{
	// This stores the minimum threshold value
	m_CannyMin = value;
	// This tells the log module that is should print the message
	LogModule::getInstance()->Info("Canny Minimum has been set to " + QString::number(value));
}
// This function returns to other modules the minimum threshold of the canny filter
int InputModule::getCannyMin()
{
	// This returns the minimum threshold value to other modules
	return m_CannyMin;
}
// This function stores the delta value set by the user in an variable
void InputModule::setDelta(double value)
{
	// This stores the delta value
	m_Delta = value;
	// This tells the log module that is should print the message
	LogModule::getInstance()->Info("Delta value has been changed to " + QString::number(value));
}
// This function returns to other modules the delta value
double InputModule::getDelta()
{
	// This returns the delta value to other modules
	return m_Delta;
}
// This function stores the scale value set by the user in an variable
void InputModule::setScale(double value)
{
	// This stores the scale value
	m_Scale = value;
	// This tells the log module that is should print the message
	LogModule::getInstance()->Info("Scale value has been changed to " + QString::number(value));
}
// This function returns to other modules the scale value
double InputModule::getScale()
{
	// This returns the scale value to other modules
	return m_Scale;
}
// This function stores the kernel size set by the user in an variable
void InputModule::setKernel(int value)
{
	// This stores the kernel size
	m_Kernelsize = value;
	// This tells the log module that is should print the message
	LogModule::getInstance()->Info("Kernel value has been changed to " + QString::number(value));
}
// This function returns to other modules the kernel size
int InputModule::getKernel()
{
	// This returns the kernel size to other modules
	return m_Kernelsize;
}
// This function loads the first available camera and provides the frames to the output display window
bool InputModule::setInputAsCamera(QCameraViewfinder *viewfinder)
{
	// Looks for the available cameras
	QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
	// If no cameras were found then print log message
	if (cameras.size() == 0) {
		// Creates a pop box with an error message to inform the user that no camera is connected
		QMessageBox::information(NULL, QString("Error"), QString("No Camera is Connected"), QMessageBox::Ok, 0);
		// This tells the log module that is should print the message
		LogModule::getInstance()->Error("Camera is not available ");
		// tells other modules that the camera is not connected
		return false;
	}
	// If camera was found
	else 
	{
		// If the camera has already been started
		if (m_camera != nullptr)
		{
			// Stops the camera
			m_camera->stop();
			// deletes the camera variable to prevent memory leaks
			delete m_camera;
		}
		// Stores the camera's name
		QString  deviceName = cameras[0].deviceName();
		// This tells the log module that is should print the message
		LogModule::getInstance()->Info("Camera " + deviceName + " has been enabled ");
		// initializes the camera
		m_camera = new QCamera(cameras[0]);
		// Displays the camera frames into the output display
		m_camera->setViewfinder(viewfinder);
		// Starts the camera
		m_camera->start();
		// returns the value of true to other modules
		return true;
	}
}
// This function stops the camera if a still image is inputted
void InputModule::setInputAsImage()
{
	// If the camera has been started
	if (m_camera != nullptr)
	{
		// Stops the camera
		m_camera->stop();
	}
	// This tells the log module that is should print the message
	LogModule::getInstance()->Info("File input mode had been enabled ");
}
