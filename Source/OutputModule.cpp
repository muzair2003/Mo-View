// This module gets the processed images from the image processing module and displays them
// It gets information from the input module to save the file and display the content of the file in the UI
// It interacts with the log module to print messages and also works with the ui controller to display all the images
#include "OutputModule.h"
#include "LogModule.h"
// instance of the class
OutputModule* OutputModule::m_instance = nullptr;

// Constructor
OutputModule::OutputModule()
{
}
// This function enables other modules to be able to call function in this module
OutputModule* OutputModule::getInstance()
{
	// if the instance is not initialized
	if (m_instance == nullptr) {
		// initialize once and carries the object of the class
		m_instance = new OutputModule();
	}
	// returns the object of the class
	return m_instance;
}
// Destructor
OutputModule::~OutputModule()
{
}
// This function saves a image file in a given file path
void OutputModule::SaveImage(cv::Mat OutputImage, QString Path)
{
	// Saves the image to a specific path
	cv::imwrite(Path.toStdString(), OutputImage);
	// Tells the log module to print an information message
	LogModule::getInstance()->Info("File has been saved");
}
// This takes a UI output window control and stores it in a variable for this module to use later
void OutputModule::setOuputGraphicsScene(QGraphicsScene* scene)
{
	// Stores the display name as a variable
	m_sceneOuput = scene;
}
// This takes a UI input window control and stores it in a variable for this module to use later
void OutputModule::setInputGraphicsScene(QGraphicsScene* scene)
{
	// Stores the display name as a public variable
	m_sceneInput = scene;
}
// This takes a UI output window control and stores it in a variable for this module to use later
void OutputModule::setOutputImageScene(QGraphicsView *Output_image)
{
	// Stores the display name as a variable
	m_Output_image = Output_image;
}
// This takes a UI input window control and stores it in a variable for this module to use later
void OutputModule::setInputImageScene(QGraphicsView *Input_image)
{
	// Stores the display name as a variable
	m_Input_image = Input_image;
}
// Display the output image with the given final image which is in Opencv format
void OutputModule::displayOutputImage(cv::Mat outputImage)
{
	// Stores the image in a QImage format 
	QImage *imageObjectOutput;
	// If the opencv image is gray or has one color channel
	if (outputImage.channels() == 1) {
		// Take all the properties of the opencv image and store it into a Qimage format
		imageObjectOutput = new QImage(outputImage.data, outputImage.cols, outputImage.rows, outputImage.step, QImage::Format_Grayscale8);
	}
	// if the opencv image has 3 color channels
	else if (outputImage.channels() == 3) {
		// Take all the properties of the opencv image and store it into a Qimage format
		imageObjectOutput = new QImage(outputImage.data, outputImage.cols, outputImage.rows, outputImage.step, QImage::Format_RGB888);
	}
	// if the opencv image has 4 color channels
	else if (outputImage.channels() == 4) {
		// Take all the properties of the opencv image and store it into a Qimage format
		imageObjectOutput = new QImage(outputImage.data, outputImage.cols, outputImage.rows, outputImage.step, QImage::Format_RGBA8888);
	}
	// if the opencv has a different amount of color channels
	else {
		// Tells the log module to print and error message
		LogModule::getInstance()->Error("unknown image file type");
	}
	// Clears the image display for the next image
	m_sceneOuput->clear();
	// This is Qt's class which is responsible for displaying images on the screen
	QPixmap image = QPixmap::fromImage(*imageObjectOutput);
	// This function is adding Pixmap to the graphic scene container of QT
	m_sceneOuput->addPixmap(image);
	// This is setting up the size of the image container
	m_sceneOuput->setSceneRect(image.rect());
	// Displays the output image into the output display
	m_Output_image->setScene(m_sceneOuput);
	// Fits the image into the display keeping the image's aspect ratio
	m_Output_image->fitInView(m_sceneOuput->sceneRect(), Qt::KeepAspectRatio);
}
// Displays the output image given the variable of the final image
void OutputModule::displayInputImage(QString filename)
{
	// Clears the image display for the next image
	m_sceneInput->clear();
	// Stores the final image in a QImage format
	QImage  *imageObject;
	// instantiates the Qimage variable
	imageObject = new QImage();
	// loading the image from the file
	imageObject->load(filename);
	// This is Qt's class which is responsible for displaying images on the screen
	QPixmap image = QPixmap::fromImage(*imageObject);
	// Makes sure the output display is empty
	m_sceneOuput->clear();
	// Displays the image in the still image display
	m_sceneInput->addPixmap(image);
	// This is setting up the size of the image container
	m_sceneInput->setSceneRect(image.rect());
	// Displays the image into the output display
	m_Input_image->setScene(m_sceneInput);
	// Fits the image into the output display
	m_Input_image->fitInView(m_sceneInput->sceneRect(), Qt::KeepAspectRatio);
}
