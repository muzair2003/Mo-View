/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcameraviewfinder.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QFormLayout *formLayout;
    QSpacerItem *verticalSpacer_10;
    QSpacerItem *verticalSpacer;
    QPushButton *Choose_Camera;
    QSpacerItem *verticalSpacer_4;
    QFrame *frame;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QSlider *Contrast;
    QSpacerItem *verticalSpacer_6;
    QLabel *label_2;
    QSlider *Brightness;
    QSpacerItem *verticalSpacer_7;
    QCheckBox *Grayscale;
    QSpacerItem *verticalSpacer_8;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *Edge_detection;
    QSpacerItem *verticalSpacer_2;
    QPushButton *Save_File;
    QSpacerItem *verticalSpacer_9;
    QLabel *label_4;
    QSpinBox *Canny_Min;
    QLabel *label_5;
    QSpinBox *Canny_Max;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QSpinBox *Kernel_Spinner;
    QDoubleSpinBox *Delta_Spinner;
    QDoubleSpinBox *Scale_Spinner;
    QPushButton *Open_File;
    QGraphicsView *Output_image;
    QLabel *Input_label;
    QLabel *Output_label;
    QGraphicsView *Input_image;
    QCameraViewfinder *viewfinder;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1771, 888);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 80, 195, 528));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        verticalSpacer_10 = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(0, QFormLayout::LabelRole, verticalSpacer_10);

        verticalSpacer = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(3, QFormLayout::LabelRole, verticalSpacer);

        Choose_Camera = new QPushButton(horizontalLayoutWidget);
        Choose_Camera->setObjectName(QString::fromUtf8("Choose_Camera"));

        formLayout->setWidget(4, QFormLayout::LabelRole, Choose_Camera);

        verticalSpacer_4 = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(5, QFormLayout::LabelRole, verticalSpacer_4);

        frame = new QFrame(horizontalLayoutWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMinimumSize(QSize(110, 200));
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Sunken);
        layoutWidget = new QWidget(frame);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 96, 185));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        Contrast = new QSlider(layoutWidget);
        Contrast->setObjectName(QString::fromUtf8("Contrast"));
        Contrast->setMaximum(200);
        Contrast->setSingleStep(1);
        Contrast->setValue(100);
        Contrast->setSliderPosition(100);
        Contrast->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(Contrast);

        verticalSpacer_6 = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_6);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);

        Brightness = new QSlider(layoutWidget);
        Brightness->setObjectName(QString::fromUtf8("Brightness"));
        Brightness->setMinimum(-50);
        Brightness->setMaximum(50);
        Brightness->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(Brightness);

        verticalSpacer_7 = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_7);

        Grayscale = new QCheckBox(layoutWidget);
        Grayscale->setObjectName(QString::fromUtf8("Grayscale"));
        Grayscale->setChecked(true);

        verticalLayout_2->addWidget(Grayscale);


        formLayout->setWidget(6, QFormLayout::LabelRole, frame);

        verticalSpacer_8 = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(7, QFormLayout::LabelRole, verticalSpacer_8);

        label_3 = new QLabel(horizontalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(9, QFormLayout::LabelRole, label_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        Edge_detection = new QComboBox(horizontalLayoutWidget);
        Edge_detection->addItem(QString());
        Edge_detection->addItem(QString());
        Edge_detection->addItem(QString());
        Edge_detection->addItem(QString());
        Edge_detection->addItem(QString());
        Edge_detection->setObjectName(QString::fromUtf8("Edge_detection"));

        horizontalLayout_2->addWidget(Edge_detection);


        formLayout->setLayout(11, QFormLayout::LabelRole, horizontalLayout_2);

        verticalSpacer_2 = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(18, QFormLayout::LabelRole, verticalSpacer_2);

        Save_File = new QPushButton(horizontalLayoutWidget);
        Save_File->setObjectName(QString::fromUtf8("Save_File"));

        formLayout->setWidget(19, QFormLayout::LabelRole, Save_File);

        verticalSpacer_9 = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(20, QFormLayout::LabelRole, verticalSpacer_9);

        label_4 = new QLabel(horizontalLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(13, QFormLayout::LabelRole, label_4);

        Canny_Min = new QSpinBox(horizontalLayoutWidget);
        Canny_Min->setObjectName(QString::fromUtf8("Canny_Min"));
        Canny_Min->setEnabled(true);
        Canny_Min->setMaximum(200);
        Canny_Min->setValue(100);

        formLayout->setWidget(13, QFormLayout::FieldRole, Canny_Min);

        label_5 = new QLabel(horizontalLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(14, QFormLayout::LabelRole, label_5);

        Canny_Max = new QSpinBox(horizontalLayoutWidget);
        Canny_Max->setObjectName(QString::fromUtf8("Canny_Max"));
        Canny_Max->setMaximum(500);
        Canny_Max->setValue(200);

        formLayout->setWidget(14, QFormLayout::FieldRole, Canny_Max);

        label_6 = new QLabel(horizontalLayoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout->setWidget(15, QFormLayout::LabelRole, label_6);

        label_7 = new QLabel(horizontalLayoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout->setWidget(16, QFormLayout::LabelRole, label_7);

        label_8 = new QLabel(horizontalLayoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        formLayout->setWidget(17, QFormLayout::LabelRole, label_8);

        Kernel_Spinner = new QSpinBox(horizontalLayoutWidget);
        Kernel_Spinner->setObjectName(QString::fromUtf8("Kernel_Spinner"));
        Kernel_Spinner->setMinimum(3);
        Kernel_Spinner->setMaximum(21);
        Kernel_Spinner->setSingleStep(2);
        Kernel_Spinner->setValue(3);

        formLayout->setWidget(17, QFormLayout::FieldRole, Kernel_Spinner);

        Delta_Spinner = new QDoubleSpinBox(horizontalLayoutWidget);
        Delta_Spinner->setObjectName(QString::fromUtf8("Delta_Spinner"));

        formLayout->setWidget(16, QFormLayout::FieldRole, Delta_Spinner);

        Scale_Spinner = new QDoubleSpinBox(horizontalLayoutWidget);
        Scale_Spinner->setObjectName(QString::fromUtf8("Scale_Spinner"));
        Scale_Spinner->setMinimum(1.000000000000000);

        formLayout->setWidget(15, QFormLayout::FieldRole, Scale_Spinner);

        Open_File = new QPushButton(horizontalLayoutWidget);
        Open_File->setObjectName(QString::fromUtf8("Open_File"));

        formLayout->setWidget(1, QFormLayout::LabelRole, Open_File);


        horizontalLayout->addLayout(formLayout);

        Output_image = new QGraphicsView(centralwidget);
        Output_image->setObjectName(QString::fromUtf8("Output_image"));
        Output_image->setGeometry(QRect(880, 150, 611, 391));
        Input_label = new QLabel(centralwidget);
        Input_label->setObjectName(QString::fromUtf8("Input_label"));
        Input_label->setGeometry(QRect(490, 80, 59, 13));
        Input_label->setAlignment(Qt::AlignCenter);
        Output_label = new QLabel(centralwidget);
        Output_label->setObjectName(QString::fromUtf8("Output_label"));
        Output_label->setGeometry(QRect(1130, 80, 67, 13));
        Output_label->setAlignment(Qt::AlignCenter);
        Input_image = new QGraphicsView(centralwidget);
        Input_image->setObjectName(QString::fromUtf8("Input_image"));
        Input_image->setGeometry(QRect(220, 150, 611, 391));
        Input_image->setMinimumSize(QSize(384, 216));
        viewfinder = new QCameraViewfinder(centralwidget);
        viewfinder->setObjectName(QString::fromUtf8("viewfinder"));
        viewfinder->setGeometry(QRect(220, 150, 611, 391));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        Choose_Camera->setText(QApplication::translate("MainWindow", "Choose Cam", nullptr));
        label->setText(QApplication::translate("MainWindow", "Contrast", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Brightness", nullptr));
        Grayscale->setText(QApplication::translate("MainWindow", "Grayscale", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Filters", nullptr));
        Edge_detection->setItemText(0, QApplication::translate("MainWindow", "Choose", nullptr));
        Edge_detection->setItemText(1, QApplication::translate("MainWindow", "Sobel", nullptr));
        Edge_detection->setItemText(2, QApplication::translate("MainWindow", "Canny", nullptr));
        Edge_detection->setItemText(3, QApplication::translate("MainWindow", "Prewitt", nullptr));
        Edge_detection->setItemText(4, QApplication::translate("MainWindow", "Laplacian", nullptr));

        Save_File->setText(QApplication::translate("MainWindow", "Save File", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Min", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Max", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "Scale", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "Delta", nullptr));
        label_8->setText(QApplication::translate("MainWindow", "Kernel Size", nullptr));
        Open_File->setText(QApplication::translate("MainWindow", "Open File", nullptr));
        Input_label->setText(QApplication::translate("MainWindow", "Input Image", nullptr));
        Output_label->setText(QApplication::translate("MainWindow", "Output Image", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
