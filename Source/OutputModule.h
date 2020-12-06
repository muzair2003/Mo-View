#pragma once
#include "opencv2\core.hpp"
#include <QString>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QCameraViewfinder>
#include "opencv2\imgcodecs.hpp"

class OutputModule
{
public:
	OutputModule();
	~OutputModule();
	static OutputModule* getInstance();
	static OutputModule* m_instance;
	void SaveImage(cv::Mat OutputImage, QString Path);
	void setOutputImageScene(QGraphicsView *Output_image);
	void setInputImageScene(QGraphicsView *Input_image);
	void setOuputGraphicsScene(QGraphicsScene* scene);
	void setInputGraphicsScene(QGraphicsScene* scene);	
	void displayOutputImage(cv::Mat outputImage);
	void displayInputImage(QString filename);
private:
	QGraphicsScene* m_sceneOuput;
	QGraphicsScene* m_sceneInput;
	QGraphicsView *m_Output_image;
	QGraphicsView *m_Input_image;

};

