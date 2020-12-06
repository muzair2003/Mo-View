#pragma once
#include "opencv2\core.hpp"
#include<QCameraViewfinder>
#include <QGraphicsView>
#include <QObject>
class ImageProcessingModule : public QObject
{
	Q_OBJECT
public:
	ImageProcessingModule();
	~ImageProcessingModule();
	static ImageProcessingModule* getInstance();
	static ImageProcessingModule* m_instance;
	void enableCameraProcessing(QCameraViewfinder *viewfinder);
	void ProcessImage();
	void disableCameraProcessing();
	cv::Mat ImageProcessingModule::returnImage();
private slots:
	void displayImageLoop();
private:
	cv::Mat Sobel(cv::Mat inputImage);
	cv::Mat Laplacian(cv::Mat inputImage);
	cv::Mat Canny(cv::Mat inputImage);
	cv::Mat Prewitt(cv::Mat inputImage);
	cv::Mat applyContrast(cv::Mat inputImage);
	cv::Mat applyBrightness(cv::Mat inputImage);
	cv::Mat applyGray(cv::Mat inputImage);
	cv::Mat applyFilter(cv::Mat inputImage);
	QTimer *m_timer;
	cv::Mat qImagetoMat(QImage* qImage);
	QCameraViewfinder *m_viewfinder;
	cv::Mat m_outputImage;
};

