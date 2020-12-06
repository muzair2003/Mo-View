#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class UIController : public QMainWindow
{
    Q_OBJECT

public:
	enum appMode
	{
		STILL_IMAGE,
		CAMERA_IMAGE
	};
    UIController(QWidget *parent = nullptr);
    ~UIController();

private slots:
    void on_Open_File_clicked();
	void on_Contrast_sliderMoved(int position);
	void on_Brightness_sliderMoved(int position);
	void on_Grayscale_stateChanged(int arg1);
	void on_Edge_detection_currentIndexChanged(const QString &arg1);
	void on_Choose_Camera_clicked();
	void on_Save_File_clicked();
	void on_Canny_Max_valueChanged(int arg1);
	void on_Canny_Min_valueChanged(int arg1);
	void on_Delta_Spinner_valueChanged(double arg1);
	void on_Scale_Spinner_valueChanged(double arg1);
	void on_Kernel_Spinner_valueChanged(int arg1);
	void resizeEvent(QResizeEvent* event);
private:
	appMode m_mode;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
