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
	cv::Mat applyContrast(cv::Mat inputImage);
	cv::Mat applyBrightness(cv::Mat inputImage);
	cv::Mat applyGray(cv::Mat inputImage);
	cv::Mat applyFilter(cv::Mat inputImage);
	void enableCameraProcessing(QCameraViewfinder *viewfinder, QGraphicsView *Output_image, QGraphicsScene*scene);
	void ProcessImage(QGraphicsView *Output_image, QGraphicsScene*scene);
	void disableCameraProcessing();
	cv::Mat ImageProcessingModule::returnImage();
private slots:
	void displayImageLoop();
private:
	QTimer *m_timer;
	cv::Mat qImagetoMat(QImage* qImage);
	QCameraViewfinder *m_viewfinder;
	QGraphicsView *m_Output_image;
	QGraphicsScene* m_scene;
	cv::Mat m_outputImage;

};

