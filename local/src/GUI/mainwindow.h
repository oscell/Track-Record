#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer> 
#include <opencv2/opencv.hpp> 

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // void on_pushButton_clicked();
    // void on_terminateButton_clicked();
    void displayVideoFeed(); 
    void on_startVideoFeedButton_clicked();
    void on_toggleSendValueButton_clicked();
    // void toggleSendValueButtonClicked();

private:
    Ui::MainWindow *ui;
    cv::VideoCapture cap;
    QTimer *timer; 
    bool videoFeedActive;
    bool sendOne; 
};

#endif // MAINWINDOW_H
