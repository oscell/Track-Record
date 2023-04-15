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
    explicit MainWindow(QWidget *parent = nullptr, const QString &serverAddress = "127.0.0.1");
    ~MainWindow();

private slots:
    void displayVideoFeed();
    void on_startVideoFeedButton_clicked();
    void on_toggleSendValueButton_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    cv::VideoCapture cap;
    bool videoFeedActive;
    bool sendOne;
    QString serverAddr; // Add this line
};

#endif // MAINWINDOW_H
