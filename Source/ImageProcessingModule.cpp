// This module takes all the data from the input module like parameters and input image
// processes the image or camera frame and sends all the data to the output module
// This module mainly consists of the following image processing algorithms
// Sobel Edge Detection
// Prewitt Edge Detection
// Canny Edge Detection
// Laplacian Edge Detection
// Contrast adjustment
// Brightness adjustment
// Convert to Grayscale
// convert from QImage to OpenCv image and vice versa

#include "ImageProcessingModule.h"
#include "ui_moView.h"
#include "InputModule.h"
#include "LogModule.h"
#include "OutputModule.h"
#include <opencv2/opencv.hpp>
#include <QCameraViewfinder>
#include <QGraphicsView>
#include <QPixmap>
#include <QTimer>
// instance of the class
ImageProcessingModule* ImageProcessingModule::m_instance = nullptr;
// Constructor
ImageProcessingModule::ImageProcessingModule() :
	m_timer(nullptr)
{
}
// This function enables other modules to be able to call function in this module
ImageProcessingModule* ImageProcessingModule::getInstance()
{
	// if the instance is not initialized
	if (m_instance == nullptr) {
		// initialize once and carries the object of the class
		m_instance = new ImageProcessingModule();
	}
	// returns the object of the class
	return m_instance;
}
// Destructor
ImageProcessingModule::~ImageProcessingModule()
{
}
// This function takes the contrast value from the input module and processes the image
cv::Mat ImageProcessingModule::applyContrast(cv::Mat inputImage)
{
	// Takes the contrast value from the input module
	int contrastValue = InputModule::getInstance()->getContrast();
	// Perform contrast adjustment on the image and returns the image
	// value adjusted by the user on the slider is an integer which varies from 0 to 200
	// here we are dividing the contrast value by 100 to get fraction value from 0 to 2
	return inputImage*contrastValue / 100.0;
}
// This function takes the brightness value from the input module and processes the image
cv::Mat ImageProcessingModule::applyBrightness(cv::Mat inputImage)
{
	// Takes the brightness value from the input module
	int brightnessValue = InputModule::getInstance()->getBrightness();
	// Performs brightness adjustment
	cv::Mat image;
	inputImage.convertTo(image, -1, 1, brightnessValue);
	// Returns the image
	return image;
}
// This function makes sure that the gray scale filter is enabled and processes the image
cv::Mat ImageProcessingModule::applyGray(cv::Mat inputImage)
{
	// Makes sure from the input module that gray scale is enabled
	bool Gray = InputModule::getInstance()->isGrayEnabled();
	// If the gray scale is enabled
	if (Gray == true)
	{
		// Stores the 3 color channels of the image
		cv::Mat BGRChannel[3];
		// Splits the image into 3 color channels
		cv::split(inputImage, BGRChannel);
		// Find the average value of the color channels
		inputImage = (BGRChannel[0] + BGRChannel[1] + BGRChannel[2]) / 3.0;
		// Returns the processed image
		return inputImage;
	}
	// returns the unprocessed image
	return inputImage;
}
// This function applies the canny edge filter with the thresholds taken from the input module
cv::Mat ImageProcessingModule::Canny(cv::Mat inputImage)
{
	// Contains output image
	cv::Mat Output;
	cv::Mat OutputTemp;

	// Blurs the image to create less noise when edge detecting
	GaussianBlur(inputImage,// input image
		OutputTemp,// output image
		cv::Size(5, 5),// smoothing pixels
		1.5);//how much the image is blurred

	// Canny filter with included threshold taken from the input module
	cv::Canny(OutputTemp,// input image
		Output,// output image
		InputModule::getInstance()->getCannyMin(),// min threshold taken from input module
		InputModule::getInstance()->getCannyMax());// max threshold taken from input module
	// Returns the processed image
	return Output;
}
// This function applies the Laplacian edge detection filter with the parameters taken from the input module
cv::Mat ImageProcessingModule::Laplacian(cv::Mat inputImage)
{
	// Contains output image
	cv::Mat Output;
	cv::Mat OutputTemp;
	// Blurs the image to create less noise when edge detecting
	GaussianBlur(inputImage, OutputTemp, cv::Size(5, 5), 0, 0, cv::BORDER_DEFAULT);
	// Applies the Laplacian edge detection method with given parameters from input module
	cv::Laplacian(OutputTemp,// input image
		Output,// output image
		CV_8U, // depth of destination image
		InputModule::getInstance()->getKernel(),// kernel size taken from input module
		InputModule::getInstance()->getScale(), //scale value taken from input module
		InputModule::getInstance()->getDelta(), //delta value taken from input module
		cv::BORDER_DEFAULT); // border type
	// Returns image
	return Output;
}
// This function applies the sobel edge detection filter with the parameters taken from the input module
cv::Mat ImageProcessingModule::Sobel(cv::Mat inputImage)
{
	// Contains output image
	cv::Mat Output;
	// Contains output image temporarily 
	cv::Mat OutputTemp;
	// Contains the edge detected images for each axis
	cv::Mat gradX, gradY;
	// Stores the parameter values taken from the input module
	int kernelSize = InputModule::getInstance()->getKernel();
	double Scale = InputModule::getInstance()->getScale();
	double Delta = InputModule::getInstance()->getDelta();
	// Blurs the image to create less noise when edge detecting
	cv::GaussianBlur(inputImage, OutputTemp, cv::Size(5, 5), 0, 0, cv::BORDER_DEFAULT);
	// Applies the sobel method to the x-axis of the image
	cv::Sobel(OutputTemp, //input image
		gradX, // output image
		CV_8U, //ddepth
		1, //x-order
		0, // y-order
		kernelSize, // kernel size take from input module
		Scale, // scale value take from input module
		Delta, // delta value take from input module
		cv::BORDER_DEFAULT); // border type

	// Applies the sobel method to the y-axis of the image
	cv::Sobel(OutputTemp, gradY, CV_8U, 0, 1, kernelSize, Scale, Delta, cv::BORDER_DEFAULT);
	// Takes the x-axis image and the y-axis image and will combines the images
	cv::addWeighted(gradX, 0.5, gradY, 0.5, 0, Output);
	// returns the image with the applied filter
	return Output;
}
// This function applies the prewitt edge detection filter with the parameters taken from the input module
cv::Mat ImageProcessingModule::Prewitt(cv::Mat inputImage)
{
	// Contains output image
	cv::Mat Output;
	// variable stores the delta value taken from the input module
	double Delta = InputModule::getInstance()->getDelta();
	// these variables  store the edge detection filter from the x-axis and y-axis
	cv::Mat gradX, gradY;
	//These variables store the 3x3 matrix that will be applied to the image for both the x-axis and y-axis
	cv::Mat_<float> PrewittX(3, 3);
	cv::Mat_<float> PrewittY(3, 3);
	// This is where the 3x3 matrix is made for the prewitt method for the x-axis
	PrewittX <<
		1, 0, -1,
		1, 0, -1,
		1, 0, -1;
	// This is where the 3x3 matrix is made for the prewitt method for the y-axis
	PrewittY << 
		1, 1, 1,
		0, 0, 0,
		-1, -1, -1;
	// Applies the 3x3 matrix for the x-axis and applies the delta value taken from the input module
	cv::filter2D(inputImage, gradX, CV_8U, PrewittX, cv::Point(-1, -1), Delta, cv::BORDER_DEFAULT);
	// Applies the 3x3 matrix for the x-axis and applies the delta value taken from the input module
	cv::filter2D(inputImage, gradY, CV_8U, PrewittY, cv::Point(-1, -1), Delta, cv::BORDER_DEFAULT);
	// Takes the x-axis image and the y-axis image and will combines the images
	cv::addWeighted(gradX, 1, gradY, 1, 0, Output);
	// returns the image with the applied prewitt filter
	return Output;

}
// This function applies the edge detection filter with the given input image and taking the filter chosen by the user from input module
cv::Mat ImageProcessingModule::applyFilter(cv::Mat inputImage)
{
	// Takes the filter the user has chosen from the input module
	QString Filter = InputModule::getInstance()->getFilter();
	// if user chooses canny edge detection
	if (Filter == "Canny")
	{
		// returns the canny filtered image
		return Canny(inputImage);
	}
	// if user chooses Laplacian edge detection
	else if (Filter == "Laplacian")
	{
		// returns the laplacian filtered image
		return Laplacian(inputImage);
	}
	//if the user has chosen sobel edge detection
	else if (Filter == "Sobel")
	{
		// returns the sobel filtered image
		return Sobel(inputImage);
	}
	// if the user has chosen prewitt edge detection
	else if (Filter == "Prewitt")
	{
		return Prewitt(inputImage);
	}
	// if the user has not chosen any edge detection
	else
	{
		// returns the same image unchanged
		return inputImage;
	}

}
// This function enables camera processing in the background with the help of a timer 
// which executes the frame processing and eventually displays the processed frame in the UI
void ImageProcessingModule::enableCameraProcessing(QCameraViewfinder *viewfinder)
{
	// stores the camera UI display window in a variable
	m_viewfinder = viewfinder;
	// Creates a timer
	m_timer = new QTimer(this);
	// After a every 50 milliseconds the camera frame will be processed
	m_timer->setInterval(50);
	// This connects the timeout signal of the timer to the function which contains the required image processing
	connect(m_timer, SIGNAL(timeout()), this, SLOT(displayImageLoop()));
	// Starts the timer
	m_timer->start();

}
// This function helps other modules disable the camera when the user chooses a still image
void ImageProcessingModule::disableCameraProcessing()
{
	// If the timer has been started before
	if (m_timer != nullptr)
	{
		// Stops the timer
		m_timer->stop();
	}
}
// This function gets called every 50 milliseconds to process all the user selected image processing to the camera frame 
void ImageProcessingModule::displayImageLoop()
{
	// Takes the current image displayed in the input image window and stores it in a variable
	QImage imageTemp = m_viewfinder->grab().toImage();
	// converts the Qimage into an opencv image
	cv::Mat image2 = qImagetoMat(&imageTemp);
	// Applies the gray scale to the image
	m_outputImage = applyGray(image2);
	// Applies the contrast adjustment to the image
	m_outputImage = applyContrast(m_outputImage);
	// Applies the brightness adjustment to the image
	m_outputImage = applyBrightness(m_outputImage);
	// Applies the appropriate edge detection filter to the image
	m_outputImage = applyFilter(m_outputImage);
	// Tells the output module to display the processed image
	OutputModule::getInstance()->displayOutputImage(m_outputImage);
}
//  This function converts the QImage format to the opencv format so it can be processed
cv::Mat ImageProcessingModule::qImagetoMat(QImage* qImage)
{
	// this stores the final opencv formatted image
	cv::Mat retImage;
	// this variable stores the format of the QImage
	QImage::Format format = qImage->format();
	// If the Qimage is a 32 bit format
	if (format == QImage::Format_RGB32)
	{
		// This creates a 4 channel Opencv image from the given QImage
		cv::Mat view(qImage->height(), qImage->width(), CV_8UC4, (void *)qImage->constBits(), qImage->bytesPerLine());
		view.copyTo(retImage);
	}
	// If the Qimage is in a 24 bit format
	else if (format == QImage::Format_RGB888)
	{
		// This creates a 3 channel Opencv image from the given QImage
		cv::Mat view(qImage->height(), qImage->width(), CV_8UC3, (void *)qImage->constBits(), qImage->bytesPerLine());
		// changes the order of the colors from RGB to BGR
		// where RGB is the order used in QT and BGR is the order used in Opencv
		cvtColor(view, retImage, cv::COLOR_RGB2BGR);
	}
	// If the Qimage is in any other bit format
	else
	{
		// convert the image from the QImage format to a 24 bit format
		QImage conv = qImage->convertToFormat(QImage::Format_RGB888);
		// This creates a 3 channel Opencv image from the given QImage
		cv::Mat view(conv.height(), conv.width(), CV_8UC3, (void *)conv.constBits(), conv.bytesPerLine());
		view.copyTo(retImage);
	}
	// returns the final image
	return retImage;
}
//  This function processes the still image
void ImageProcessingModule::ProcessImage()
{
	// Asks the input module for the still image and applies the gray scale filter
	m_outputImage = applyGray(InputModule::getInstance()->getImage());
	// Applies contrast adjustment to the image
	m_outputImage = applyContrast(m_outputImage);
	// Applies brightness adjustment to the image
	m_outputImage = applyBrightness(m_outputImage);
	// Applies edge detection filters to the image
	m_outputImage = applyFilter(m_outputImage);
	// Makes sure the colors translate when the image are converted since QT uses RGB and Opencv uses BGR
	cv::cvtColor(m_outputImage, m_outputImage, cv::COLOR_BGR2RGB);
	// Tells the output module to display the given image
	OutputModule::getInstance()->displayOutputImage(m_outputImage);

}
// This function returns the processed image data if the user wants to save it
cv::Mat ImageProcessingModule::returnImage()
{
	// if the output image file is not empty
	if (!m_outputImage.empty()) {
		// Makes sure the colors translate when the image are converted since QImage uses RGB and Opencv uses BGR
		cv::cvtColor(m_outputImage, m_outputImage, cv::COLOR_BGR2RGB);
		// returns the final image
		return m_outputImage;
	}
	// if the processed image file is empty
	else {
		// Tells log to print the appropriate message
		LogModule::getInstance()->Error("Cannot save empty output image");
		// returns the empty image which was given
		return cv::Mat();
	}
}