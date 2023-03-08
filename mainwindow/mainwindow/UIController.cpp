#include "UIController.h"
#include "ui_mainwindow.h"
#include "OutputModule.h"
#include <QFileDialog>
#include <QCamera>
#include <QCameraInfo>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QCameraImageCapture>
#include "InputModule.h"
#include "LogModule.h"
#include "ImageProcessingModule.h"


UIController::UIController(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
	, m_mode(appMode::STILL_IMAGE)
{
	// Hides all the parameters fof the edge detection method
    ui->setupUi(this);
	ui->Canny_Min->setVisible(false);
	ui->Canny_Max->setVisible(false);
	ui->label_4->setVisible(false);
	ui->label_5->setVisible(false);
	ui->label_6->setVisible(false);
	ui->label_7->setVisible(false);
	ui->label_8->setVisible(false);
	ui->Scale_Spinner->setVisible(false);
	ui->Delta_Spinner->setVisible(false);
	ui->Kernel_Spinner->setVisible(false);
}

UIController::~UIController()
{
    delete ui;
}
// This functions lets the user choose an image from their device with a popup menu
void UIController::on_Open_File_clicked()
{
	// Gets the file path of the still image from the user
    QString filename=QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://",
				// Prevents the user from choosing an invalid file
                "Image File(*.png;*.jpg;*.bmp);;");
	// Sends the file path to the input module
	InputModule::getInstance()->setImageFilename(filename);
    imageObject = new QImage();
    imageObject->load(filename);
    image = QPixmap::fromImage(*imageObject);
    scene = new QGraphicsScene(this);
    scene->addPixmap(image);
    scene->setSceneRect(image.rect());
    ui->Input_image->setScene(scene);
    ui->Input_image->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
	m_mode = STILL_IMAGE;
	// Tells the input module that the input image is the one chosen by the user
	InputModule::getInstance()->setInputAsImage();
	// Tells image processing to disable the camera since a still image was chosen
	ImageProcessingModule::getInstance()->disableCameraProcessing();
	ui->viewfinder->hide();
	return;
}
// This function 
void UIController::on_Contrast_sliderMoved(int position)
{
	InputModule::getInstance()->setContrast(position);
	if (m_mode == STILL_IMAGE)
	{
		ImageProcessingModule::getInstance()->ProcessImage(ui->Output_image, new QGraphicsScene(this));
	}
}
void UIController::on_Brightness_sliderMoved(int position)
{
	InputModule::getInstance()->setBrightness(position);
	if (m_mode == STILL_IMAGE)
	{
		ImageProcessingModule::getInstance()->ProcessImage(ui->Output_image, new QGraphicsScene(this));
	}

}
void UIController::on_Grayscale_stateChanged(int arg1)
{
	if (arg1 == 2) {
		InputModule::getInstance()->enableGray(true);
	}
	else
	{
		InputModule::getInstance()->enableGray(false);
	}
	if (m_mode == STILL_IMAGE)
	{
		ImageProcessingModule::getInstance()->ProcessImage(ui->Output_image, new QGraphicsScene(this));
	}
}

void UIController::on_Edge_detection_currentIndexChanged(const QString &arg1)
{
	InputModule::getInstance()->setFilter(arg1);
	ui->Canny_Min->setVisible(false);
	ui->Canny_Max->setVisible(false);
	ui->label_4->setVisible(false);
	ui->label_5->setVisible(false);
	ui->label_6->setVisible(false);
	ui->label_7->setVisible(false);
	ui->label_8->setVisible(false);
	ui->Scale_Spinner->setVisible(false);
	ui->Delta_Spinner->setVisible(false);
	ui->Kernel_Spinner->setVisible(false);

	if (arg1 == "Canny")
	{
		ui->Canny_Min->setVisible(true);
		ui->Canny_Max->setVisible(true);
		ui->label_4->setVisible(true);
		ui->label_5->setVisible(true);
	}
	else if (arg1 == "Laplacian" || arg1 =="Sobel")
	{
		ui->label_6->setVisible(true);
		ui->label_7->setVisible(true);
		ui->label_8->setVisible(true);
		ui->Scale_Spinner->setVisible(true);
		ui->Delta_Spinner->setVisible(true);
		ui->Kernel_Spinner->setVisible(true);
	}
	else if(arg1 == "Prewitt")
	{
		ui->label_7->setVisible(true);
		ui->Delta_Spinner->setVisible(true);
	}
	if (m_mode == STILL_IMAGE)
	{
		ImageProcessingModule::getInstance()->ProcessImage(ui->Output_image, new QGraphicsScene(this));
	}
}
void UIController::on_Choose_Camera_clicked()
{
	ui->viewfinder->show();

	m_mode = CAMERA_IMAGE;
	InputModule::getInstance()->setInputAsCamera(ui->viewfinder);
	ImageProcessingModule::getInstance()->enableCameraProcessing(ui->viewfinder, ui->Output_image, new QGraphicsScene(this));
}
void UIController::on_Save_File_clicked()
{
	cv::Mat ret_image;
	ret_image = ImageProcessingModule::getInstance()->returnImage();
	QString imagePath = QFileDialog::getSaveFileName(
		this,
		tr("Save File"),
		"",
		tr("JPEG (*.jpg *.jpeg);;PNG (*.png)")
	);
	OutputModule::getInstance()->SaveImage(ret_image, imagePath);
}
void UIController::on_Canny_Max_valueChanged(int arg1)
{
	InputModule::getInstance()->setCannyMax(arg1);
	if (m_mode == STILL_IMAGE)
	{
		ImageProcessingModule::getInstance()->ProcessImage(ui->Output_image, new QGraphicsScene(this));
	}

}
void UIController::on_Canny_Min_valueChanged(int arg1)
{
	InputModule::getInstance()->setCannyMin(arg1);
	if (m_mode == STILL_IMAGE)
	{
		ImageProcessingModule::getInstance()->ProcessImage(ui->Output_image, new QGraphicsScene(this));
	}
}
void UIController::on_Delta_Spinner_valueChanged(double arg1)
{
	InputModule::getInstance()->setDelta(arg1);
	if (m_mode == STILL_IMAGE)
	{
		ImageProcessingModule::getInstance()->ProcessImage(ui->Output_image, new QGraphicsScene(this));
	}
}
void UIController::on_Scale_Spinner_valueChanged(double arg1)
{
	InputModule::getInstance()->setScale(arg1);
	if (m_mode == STILL_IMAGE)
	{
		ImageProcessingModule::getInstance()->ProcessImage(ui->Output_image, new QGraphicsScene(this));
	}
}
void UIController::on_Kernel_Spinner_valueChanged(int arg1)
{
	InputModule::getInstance()->setKernel(arg1);
	if (m_mode == STILL_IMAGE)
	{
		ImageProcessingModule::getInstance()->ProcessImage(ui->Output_image, new QGraphicsScene(this));
	}
}