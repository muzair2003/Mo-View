#include "UIController.h"
#include <QApplication>
#include <QDir>

int main(int argc, char *argv[])
{
	// This is QT's application framework
    QApplication application(argc, argv);
	// instantiating the ui controller and showing the ui window
    UIController ui_controller;
	ui_controller.setWindowTitle(QDir::currentPath());
	ui_controller.show();
	// This launches the event loop for all QT related calls
    return application.exec();
}
