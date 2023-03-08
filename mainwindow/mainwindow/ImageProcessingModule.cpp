#include "ImageProcessingModule.h"
#include "ui_mainwindow.h"
#include "InputModule.h"
#include <opencv2/opencv.hpp>
#include <QCameraViewfinder>
#include <QGraphicsView>
#include <QPixmap>
#include <QTimer>
#include "LogModule.h"



ImageProcessingModule* ImageProcessingModule::m_instance = nullptr;


ImageProcessingModule::ImageProcessingModule():
	m_timer(nullptr)
	//InputModule::getInstance()->ge
{
}

ImageProcessingModule* ImageProcessingModule::getInstance()
{
	if (m_instance == nullptr) {
		m_instance = new ImageProcessingModule();
	}
	return m_instance;
}
ImageProcessingModule::~ImageProcessingModule()
{
}



cv::Mat ImageProcessingModule::applyContrast(cv::Mat inputImage)
{
	int contrastValue = InputModule::getInstance()->getContrast();
	// perform contrast adjustment
	return inputImage*contrastValue / 100.0;
}
cv::Mat ImageProcessingModule::applyBrightness(cv::Mat inputImage)
{
	int brightnessValue = InputModule::getInstance()->getBrightness();
	// perfomr contrast adjustment
	cv::Mat image;
	inputImage.convertTo(image, -1, 1, brightnessValue);
	return image;
}
cv::Mat ImageProcessingModule::applyGray(cv::Mat inputImage)
{
	bool Gray = InputModule::getInstance()->isGrayEnabled();
	// perfomr contrast adjustment
	if (Gray == true)
	{
		cv::cvtColor(inputImage, inputImage, cv::COLOR_RGB2GRAY);
		return inputImage;
	}
	return inputImage;
}
cv::Mat Canny(cv::Mat inputImage)
{
	cv::Mat Output;// Contains output image
	cv::Mat OutputTemp;

	//cv::cvtColor(inputImage, Output, cv::COLOR_BGR2GRAY);// convert to grayscale

	GaussianBlur(inputImage,// input image
		OutputTemp,// output image
		cv::Size(5, 5),// smoothing pixels
		1.5);//how much the image is blurred

	Canny(OutputTemp,// input image
		Output,// output image
		InputModule::getInstance()->getCannyMin(),// min threshold
		InputModule::getInstance()->getCannyMax());// max threshold
	return Output;
}
cv::Mat Laplacian(cv::Mat inputImage)
{
	cv::Mat Output;// Contains output image
	cv::Mat OutputTemp;
	GaussianBlur(inputImage, OutputTemp, cv::Size(5, 5), 0, 0, cv::BORDER_DEFAULT); // blurs the image

	//cvtColor(Output, Output, cv::COLOR_RGB2GRAY); // makes the image into grayscale

												  //Laplacian edge detection method
	Laplacian(OutputTemp,// input image
		Output,// output image
		CV_8U, // depth of destination image
		InputModule::getInstance()->getKernel(), // kernel size
		InputModule::getInstance()->getScale(), //scale value
		InputModule::getInstance()->getDelta(), //delta value
		cv::BORDER_DEFAULT); // border type
	return Output;
}
cv::Mat Sobel(cv::Mat inputImage)
{
	cv::Mat Output;// Contains output image
	cv::Mat OutputTemp;
	cv::Mat gradX, gradY;
	GaussianBlur(inputImage, OutputTemp, cv::Size(5, 5), 0, 0, cv::BORDER_DEFAULT);
	//Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
	int kernelSize = InputModule::getInstance()->getKernel();
	double Scale = InputModule::getInstance()->getScale();
	double Delta = InputModule::getInstance()->getDelta();
	Sobel(OutputTemp, gradX, CV_8U, 1, 0, kernelSize, Scale, Delta, cv::BORDER_DEFAULT);

	//Gradient Y
	//Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
	Sobel(OutputTemp, gradY, CV_8U, 0, 1, kernelSize, Scale, Delta, cv::BORDER_DEFAULT);

	//Total Gradient (approximate)
	addWeighted(gradX, 0.5, gradY, 0.5, 0, Output);
	return Output;
}
cv::Mat Prewitt(cv::Mat inputImage)
{
	cv::Mat Output;// Contains output image
	double Delta = InputModule::getInstance()->getDelta();
	cv::Mat gradX, gradY;
	cv::Mat_<float> PrewittX(3, 3);
	cv::Mat_<float> PrewittY(3, 3);
	PrewittX <<
		1, 0, -1,
		1, 0, -1,
		1, 0, -1;
	PrewittY <<
		1, 1, 1,
		0, 0, 0,
		-1, -1, -1;
	cv::filter2D(inputImage, gradX, CV_8U, PrewittX, cv::Point(-1, -1), Delta, cv::BORDER_DEFAULT);
	cv::filter2D(inputImage, gradY, CV_8U, PrewittY, cv::Point(-1, -1), Delta, cv::BORDER_DEFAULT);
	addWeighted(gradX, 1, gradY, 1, 0, Output);
	return Output;

}
cv::Mat ImageProcessingModule::applyFilter(cv::Mat inputImage)
{
	QString Filter = InputModule::getInstance()->getFilter();

	if (Filter == "Canny")  // if user chooses canny edge detection
	{
		return Canny(inputImage);
	}
	else if (Filter == "Laplacian") // if user chooses Laplacian edge detection
	{
		return Laplacian(inputImage);
	}
	else if (Filter == "Sobel") 
	{
		return Sobel(inputImage);
	}
	else if (Filter == "Prewitt") 
	{
		return Prewitt(inputImage);
	}
	else
	{
		return inputImage;
	}

}
void ImageProcessingModule::enableCameraProcessing(QCameraViewfinder *viewfinder, QGraphicsView *Output_image, QGraphicsScene*scene)
{
	m_viewfinder = viewfinder;
	m_Output_image = Output_image;
	m_scene = scene;

	m_timer = new QTimer(this);
	m_timer->setInterval(50);
	connect(m_timer, SIGNAL(timeout()), this, SLOT(displayImageLoop()));
	m_timer->start();

}
void ImageProcessingModule::disableCameraProcessing()
{
	if (m_timer != nullptr)
	{
		m_timer->stop();
	}
}
void ImageProcessingModule::displayImageLoop()
{
	QImage  *imageObjectOutput;
	QImage imageTemp = m_viewfinder->grab().toImage();
	cv::Mat image2 = qImagetoMat(&imageTemp);

	m_outputImage = applyGray(image2);
	m_outputImage = applyContrast(m_outputImage);
	m_outputImage = applyBrightness(m_outputImage);
	m_outputImage = applyFilter(m_outputImage);

	if (m_outputImage.channels() == 1) {
		imageObjectOutput = new QImage(m_outputImage.data, m_outputImage.cols, m_outputImage.rows, m_outputImage.step, QImage::Format_Grayscale8);
	}
	else if (m_outputImage.channels() == 3) {
		imageObjectOutput = new QImage(m_outputImage.data, m_outputImage.cols, m_outputImage.rows, m_outputImage.step, QImage::Format_RGB888);
	}
	else if (m_outputImage.channels() == 4) {
		imageObjectOutput = new QImage(m_outputImage.data, m_outputImage.cols, m_outputImage.rows, m_outputImage.step, QImage::Format_RGBA8888);
	}
	else {
		LogModule::getInstance()->Error("unknown image file type");
	}

	QPixmap image = QPixmap::fromImage(*imageObjectOutput);
	m_scene->addPixmap(image);
	m_scene->setSceneRect(image.rect());
	m_Output_image->setScene(m_scene);
	m_Output_image->fitInView(m_scene->sceneRect(), Qt::KeepAspectRatio);
}
cv::Mat ImageProcessingModule::qImagetoMat(QImage* qImage)
{
	cv::Mat retImage;
	switch (qImage->format()) {

		case QImage::Format_RGB32:
		{
			cv::Mat view(qImage->height(), qImage->width(), CV_8UC4, (void *)qImage->constBits(), qImage->bytesPerLine());
			view.copyTo(retImage);
			break;
		}
		case QImage::Format_RGB888:
		{
			cv::Mat view(qImage->height(), qImage->width(), CV_8UC3, (void *)qImage->constBits(), qImage->bytesPerLine());
			cvtColor(view, retImage, cv::COLOR_RGB2BGR);
			break;
		}
		default:
		{
			QImage conv = qImage->convertToFormat(QImage::Format_RGB888);
			cv::Mat view(conv.height(), conv.width(), CV_8UC3, (void *)conv.constBits(), conv.bytesPerLine());
			view.copyTo(retImage);
			break;
		}
	}
	return retImage;
}
void ImageProcessingModule::ProcessImage(QGraphicsView *Output_image, QGraphicsScene*scene)
{
	QImage *imageObjectOutput;
	m_outputImage = applyGray(InputModule::getInstance()->getImage());
	m_outputImage = applyContrast(m_outputImage);
	m_outputImage = applyBrightness(m_outputImage);
	m_outputImage = applyFilter(m_outputImage);
	cv::cvtColor(m_outputImage, m_outputImage, cv::COLOR_BGR2RGB);
	if (m_outputImage.channels() == 1) {
		imageObjectOutput = new QImage(m_outputImage.data, m_outputImage.cols, m_outputImage.rows, m_outputImage.step, QImage::Format_Grayscale8);
	}
	else if (m_outputImage.channels() == 3) {
		imageObjectOutput = new QImage(m_outputImage.data, m_outputImage.cols, m_outputImage.rows, m_outputImage.step, QImage::Format_RGB888);
	}
	else if (m_outputImage.channels() == 4) {
		imageObjectOutput = new QImage(m_outputImage.data, m_outputImage.cols, m_outputImage.rows, m_outputImage.step, QImage::Format_RGBA8888);
	}
	else {
		LogModule::getInstance()->Error("unknown image file type");
	}

	QPixmap image = QPixmap::fromImage(*imageObjectOutput);
	scene->addPixmap(image);
	scene->setSceneRect(image.rect());
	Output_image->setScene(scene);
	Output_image->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}
cv::Mat ImageProcessingModule::returnImage()
{
	cv::cvtColor(m_outputImage, m_outputImage, cv::COLOR_BGR2RGB);
	return m_outputImage;
}