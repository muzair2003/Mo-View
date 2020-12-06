// This module is responsible for capturing all the following information from the user 
// input image Filename
// output image filename
// brightness value
// contrast value
// grayscale state
// edge detection selection
// all filter related parameters
// provides controls to display all the images to other modules
#include "UIController.h"
#include "ui_moView.h"
#include "OutputModule.h"
#include "InputModule.h"
#include "LogModule.h"
#include "ImageProcessingModule.h"
#include <QFileDialog>

// constructor
UIController::UIController(QWidget *parent)
//calls the constructor for main window's superclass
	: QMainWindow(parent)
	// constructs the ui member
	, ui(new Ui::MainWindow)
	// sets the mode to a still image mode as a default
	, m_mode(appMode::STILL_IMAGE)
{
	ui->setupUi(this);
	// Hides all the parameters of the edge detection method by default
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

	// give output module access to all the UI controls to display the input and output images
	OutputModule::getInstance()->setOuputGraphicsScene(new QGraphicsScene(this));
	OutputModule::getInstance()->setInputGraphicsScene(new QGraphicsScene(this));
	OutputModule::getInstance()->setOutputImageScene(ui->Output_image);
	OutputModule::getInstance()->setInputImageScene(ui->Input_image);
}
// Destructor
UIController::~UIController()
{
	// This function deletes the ui to prevent memory leaks
	delete ui;
}
// This functions lets the user choose an image from their device with a open file dialog
void UIController::on_Open_File_clicked()
{
	// Gets the file path of the still image from the user
	QString filename = QFileDialog::getOpenFileName(
		// Pointer to the caller class
		this,
		// The title of the pop up tab
		"Open File",
		// The start path of pop up tab
		"C://",
		// Prevents the user from choosing an invalid file
		"Image File(*.png;*.jpg;*.jpeg;*.bmp;);;");
	// if the file chosen by the user is not empty
	if (!filename.isEmpty()) {
		// Sends the file path to the input module
		InputModule::getInstance()->setImageFilename(filename);
		// Changes the mode to a still image so other modules know if they display a still image
		m_mode = STILL_IMAGE;
		// Makes sure the still image display is showing and not the camera image display on the input image window
		ui->stackedWidget->setCurrentIndex(0);
		// Tells the path of the still image to the output module
		OutputModule::getInstance()->displayInputImage(filename);
		// Tells the input module that the input image is the one chosen by the user
		InputModule::getInstance()->setInputAsImage();
		// Tells image processing to disable the camera since a still image was chosen
		ImageProcessingModule::getInstance()->disableCameraProcessing();
		// Turns off the camera display since we are going to display a still image
		ui->viewfinder->hide();
		// Enables all the UI controls to process an image
		ui->Brightness->setEnabled(true);
		ui->Contrast->setEnabled(true);
		ui->Edge_detection->setEnabled(true);
		ui->Grayscale->setEnabled(true);
		ui->Save_File->setEnabled(true);
		// Tells image processing module to process the image with the given value
		ImageProcessingModule::getInstance()->ProcessImage();
	}
	// ends the function 
	return;
}
// This function gets called when the user changes the contrast position on the slider
void UIController::on_Contrast_sliderMoved(int position)
{
	// Tells the input module to save the contrast value
	InputModule::getInstance()->setContrast(position);
	// Checks if a still image is inputted
	if (m_mode == STILL_IMAGE)
	{
		// Makes sure the still image display is showing and not the camera image display
		ui->stackedWidget->setCurrentIndex(0);
		// Tells image processing module to process the image with the given value
		ImageProcessingModule::getInstance()->ProcessImage();
	}
}
// This function gets called when the user changes the brightness value on the slider
void UIController::on_Brightness_sliderMoved(int position)
{
	// Tells the input module to save the brightness value
	InputModule::getInstance()->setBrightness(position);
	// Checks if a still image is inputted
	if (m_mode == STILL_IMAGE)
	{
		// Tells image processing module to process the image with the given value
		ImageProcessingModule::getInstance()->ProcessImage();
	}
}
// This function is called when the user selects the gray scale filter
void UIController::on_Grayscale_stateChanged(int arg1)
{
	// If the gray scale check box is checked
	if (arg1 == 2) {
		// Tell the input module that user would like to apply gray scale
		InputModule::getInstance()->enableGray(true);
	}
	// If the gray scale check box is unchecked
	else
	{
		// Tell the input module that user would not like to apply gray scale
		InputModule::getInstance()->enableGray(false);
	}
	// Checks if a still image is inputted
	if (m_mode == STILL_IMAGE)
	{
		// Tells the image processing module to start processing the image
		ImageProcessingModule::getInstance()->ProcessImage();
	}
}
// This function is called when the user changes the chosen edge detection method value
void UIController::on_Edge_detection_currentIndexChanged(const QString &arg1)
{
	// Gets the edge detection filter from the input module
	InputModule::getInstance()->setFilter(arg1);
	// Hides all the variable parameters when no edge detection is chosen
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
	// If the user chooses the canny edge detection method
	if (arg1 == "Canny")
	{
		// Shows the canny parameters to the user in the ui
		ui->Canny_Min->setVisible(true);
		ui->Canny_Max->setVisible(true);
		ui->label_4->setVisible(true);
		ui->label_5->setVisible(true);
	}
	// If the user chooses the Laplacian or Sobel edge detection methods
	else if (arg1 == "Laplacian" || arg1 == "Sobel")
	{
		// Shows the scale, delta and kernel size values to the user in the ui
		ui->label_6->setVisible(true);
		ui->label_7->setVisible(true);
		ui->label_8->setVisible(true);
		ui->Scale_Spinner->setVisible(true);
		ui->Delta_Spinner->setVisible(true);
		ui->Kernel_Spinner->setVisible(true);
	}
	// If the user chooses the Prewitt edge detection method
	else if (arg1 == "Prewitt")
	{
		// Show the delta value to the user in the ui
		ui->label_7->setVisible(true);
		ui->Delta_Spinner->setVisible(true);
	}
	// Checks if a still image is inputted
	if (m_mode == STILL_IMAGE)
	{
		// Tells the image processing module to apply the appropriate edge detection method to the image
		ImageProcessingModule::getInstance()->ProcessImage();
	}
}
// This function is called when the user clicks 
void UIController::on_Choose_Camera_clicked()
{
	// makes sure the camera display can be viewed by the user
	ui->viewfinder->show();
	// Changes the display mode to a camera mode
	m_mode = CAMERA_IMAGE;
	// Makes sure the camera display is showing not the still image display
	ui->stackedWidget->setCurrentIndex(1);

	// Tells the input module show the camera in the input display
	if (InputModule::getInstance()->setInputAsCamera(ui->viewfinder)) {
		// Make sure that user can use the filter slider and buttons
		ui->Brightness->setEnabled(true);
		ui->Contrast->setEnabled(true);
		ui->Edge_detection->setEnabled(true);
		ui->Grayscale->setEnabled(true);
		ui->Save_File->setEnabled(true);
		// Tells the image processing module to allow for the frames to be processed
		ImageProcessingModule::getInstance()->enableCameraProcessing(ui->viewfinder);
	}
}
// This function gets called when the user clicks on the save file button
void UIController::on_Save_File_clicked()
{
	// Stores the final image that will be saved
	cv::Mat ret_image;
	// Ask the image processing module for the filtered image
	ret_image = ImageProcessingModule::getInstance()->returnImage();
	// Gets and stores the path which the file be saved in
	QString imagePath = QFileDialog::getSaveFileName(
		// Pointer to the class
		this,
		// Name of the pop up tab
		"Save File",
		// the default path of the pop up tab 
		"",
		// The format the file will be saved in
		"JPEG (*.jpg *.jpeg);;PNG (*.png)");
	// if the file path is not blank 
	if (!imagePath.isEmpty()) {
		// Tells the output module to save the given file to the given path
		OutputModule::getInstance()->SaveImage(ret_image, imagePath);
	}
}
// This function is called when the maximum threshold for the canny filtered is changed
void UIController::on_Canny_Max_valueChanged(int arg1)
{
	// Tells the input module the max threshold of the canny filter
	InputModule::getInstance()->setCannyMax(arg1);
	// Checks if a still image is inputted
	if (m_mode == STILL_IMAGE)
	{
		// Tells the image processing module to process the image with the given parameters
		ImageProcessingModule::getInstance()->ProcessImage();
	}

}
// This function is called when the minimum threshold for the canny filtered is changed
void UIController::on_Canny_Min_valueChanged(int arg1)
{
	// Tells the input module the minimum threshold of the canny image
	InputModule::getInstance()->setCannyMin(arg1);
	// Checks if a still image is inputted
	if (m_mode == STILL_IMAGE)
	{
		// Tells the image processing module to process the image with the given parameters
		ImageProcessingModule::getInstance()->ProcessImage();
	}
}
// This function is called when the delta value is changed
void UIController::on_Delta_Spinner_valueChanged(double arg1)
{
	// Tells the input module the delta value
	InputModule::getInstance()->setDelta(arg1);
	// Checks if a still image is inputted
	if (m_mode == STILL_IMAGE)
	{
		// Tells the image processing module to process the image with the given parameters
		ImageProcessingModule::getInstance()->ProcessImage();
	}
}
// This function is called when the scale value is changed
void UIController::on_Scale_Spinner_valueChanged(double arg1)
{
	// Tells the input module the scale value
	InputModule::getInstance()->setScale(arg1);
	// Checks if a still image is inputted
	if (m_mode == STILL_IMAGE)
	{
		// Tells the image processing module to process the image with the given parameters
		ImageProcessingModule::getInstance()->ProcessImage();
	}
}
// This function is called when the kernel size is changed
void UIController::on_Kernel_Spinner_valueChanged(int arg1)
{
	// Tells the input module the kernel size
	InputModule::getInstance()->setKernel(arg1);
	// Checks if a still image is inputted
	if (m_mode == STILL_IMAGE)
	{
		// Tells the image processing module to process the image with the given parameters
		ImageProcessingModule::getInstance()->ProcessImage();
	}
}
// Makes sure the displays stay a certain dimension when the program is changed in size
void UIController::resizeEvent(QResizeEvent* event)
{
	// Make sure the input and output displays fill the screen when the tab shape is changed
	QMainWindow::resizeEvent(event);
	// reloading and redrawing the input image
	QString filename = InputModule::getInstance()->getImageFilename();
	// Checks if the file chosen by the user is empty
	if (!filename.isEmpty()) {
		// Tells the output module to display the input image
		OutputModule::getInstance()->displayInputImage(filename);
		// Checks if a still image is inputted
		if (m_mode == STILL_IMAGE)
		{
			// Tells the image processing module to process the image with the given parameters
			ImageProcessingModule::getInstance()->ProcessImage();
		}
	}
}