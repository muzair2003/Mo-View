#include "UIController.h"
#include <QApplication>
#include <QDir>
#include "iostream"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

int function_call(string Method);
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UIController w;
    w.setWindowTitle(QDir::currentPath());
    w.show();
   // function_call("Gray");
    cv::waitKey(0);
    return a.exec();
}
