/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *mainLayout;
    QLabel *logoLabel;
    QHBoxLayout *videoFeedLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *videoFeedLabel;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *buttonsLayout;
    QPushButton *pushButton;
    QPushButton *terminateButton;
    QPushButton *startVideoFeedButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        mainLayout = new QVBoxLayout(centralwidget);
        mainLayout->setObjectName("mainLayout");
        logoLabel = new QLabel(centralwidget);
        logoLabel->setObjectName("logoLabel");
        logoLabel->setPixmap(QPixmap(QString::fromUtf8("Logo.png")));
        logoLabel->setAlignment(Qt::AlignCenter);

        mainLayout->addWidget(logoLabel);

        videoFeedLayout = new QHBoxLayout();
        videoFeedLayout->setObjectName("videoFeedLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        videoFeedLayout->addItem(horizontalSpacer);

        videoFeedLabel = new QLabel(centralwidget);
        videoFeedLabel->setObjectName("videoFeedLabel");
        videoFeedLabel->setFrameShape(QFrame::StyledPanel);
        videoFeedLabel->setFrameShadow(QFrame::Sunken);
        videoFeedLabel->setScaledContents(true);

        videoFeedLayout->addWidget(videoFeedLabel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        videoFeedLayout->addItem(horizontalSpacer_2);


        mainLayout->addLayout(videoFeedLayout);

        buttonsLayout = new QHBoxLayout();
        buttonsLayout->setObjectName("buttonsLayout");
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");

        buttonsLayout->addWidget(pushButton);

        terminateButton = new QPushButton(centralwidget);
        terminateButton->setObjectName("terminateButton");

        buttonsLayout->addWidget(terminateButton);

        startVideoFeedButton = new QPushButton(centralwidget);
        startVideoFeedButton->setObjectName("startVideoFeedButton");

        buttonsLayout->addWidget(startVideoFeedButton);


        mainLayout->addLayout(buttonsLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 20));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        videoFeedLabel->setText(QString());
        pushButton->setText(QCoreApplication::translate("MainWindow", "Start Executable", nullptr));
        terminateButton->setText(QCoreApplication::translate("MainWindow", "Terminate Executable", nullptr));
        startVideoFeedButton->setText(QCoreApplication::translate("MainWindow", "Start Video Feed", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
