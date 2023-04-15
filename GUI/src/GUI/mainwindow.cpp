#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QMessageBox"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <QTimer>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <QStyle>

QString readStyleSheet(const QString &file_path) {
    QFile file(file_path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return QString();
    }

    QTextStream in(&file);
    QString styleSheet = in.readAll();
    file.close();

    return styleSheet;
}

MainWindow::MainWindow(QWidget *parent, const QString &serverAddress)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , serverAddr(serverAddress)
{
    ui->setupUi(this);

    // Read and apply the CSS stylesheet
    setStyleSheet(readStyleSheet("../src/GUI/styles.css"));

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::displayVideoFeed);
    videoFeedActive = false;

    // Disconnect any existing connections and reconnect the signal to the slot
    disconnect(ui->toggleSendValueButton, &QPushButton::clicked, nullptr, nullptr);
    connect(ui->toggleSendValueButton, &QPushButton::clicked, this, &MainWindow::on_toggleSendValueButton_clicked);

    ui->toggleSendValueButton->setProperty("trackingActive", false);
    ui->startVideoFeedButton->setProperty("videoFeedActive", false);
    sendOne = true;
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayVideoFeed()
{
    cv::Mat frame;
    if (!cap.read(frame)) {
        perror("Video Feed Error, Failed to read a video frame.");
        return;
    }

    cv::CascadeClassifier face_det;
    if(!face_det.load("/usr/local/share/opencv4/haarcascades/haarcascade_frontalface_default.xml"))
    {
        std::cerr << "Error loading the model, check opencv installation and the cascade libraries" << std::endl;
    }

    int x_frame_centr = (frame.cols*0.5);
    int y_frame_centr = (frame.rows*0.5);

    cv::flip(frame, frame, 1);

    std::vector<cv::Rect> faces;
    face_det.detectMultiScale(frame, faces);

    for (const auto& face : faces)
    {
        cv::rectangle(frame, face, cv::Scalar(0, 255, 0), 2);

        int x_face_centr = (face.x + face.width * 0.5);
        int y_face_centr = (face.y + face.height * 0.5);

        cv::rectangle(frame, cv::Point(x_face_centr-5,y_face_centr-5), cv::Point(x_face_centr+5,y_face_centr+5), cv::Scalar(255,255,255),1);
    }

    // Convert the cv::Mat to QImage
    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
    QImage img(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);

    // Display the QImage on the QLabel
    ui->videoFeedLabel->setPixmap(QPixmap::fromImage(img));
    ui->videoFeedLabel->resize(img.size());
}

void MainWindow::on_startVideoFeedButton_clicked()
{
    if (!videoFeedActive) {
        cap.open(0); // Reconnect to the webcam
        timer->start(30); // Start the video feed
        ui->startVideoFeedButton->setText("Stop Video Feed"); // Change the button text
        ui->startVideoFeedButton->setProperty("videoFeedActive", true);
        videoFeedActive = true; // Update the videoFeedActive variable
    } else {
        timer->stop(); // Stop the video feed
        cap.release(); // Disconnect from the webcam
        ui->startVideoFeedButton->setText("Start Video Feed"); // Change the button text

        // Clear the QLabel displaying the video feed
        ui->videoFeedLabel->setPixmap(QPixmap());
        ui->startVideoFeedButton->setProperty("videoFeedActive", false);
        videoFeedActive = false; // Update the videoFeedActive variable
    }

    ui->startVideoFeedButton->style()->unpolish(ui->startVideoFeedButton);
    ui->startVideoFeedButton->style()->polish(ui->startVideoFeedButton);
}


void MainWindow::on_toggleSendValueButton_clicked()
{
    // Create a socket
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd < 0) {
        perror("Socket creation failed");
        return;
    }

    // Connect to the server
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(serverAddr.toStdString().c_str());
    server_addr.sin_port = htons(8080);
    
    if (::connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        QMessageBox msgBox;
        msgBox.setText("Connection to server failed");
        msgBox.exec();
        ::close(client_fd);
        return;
    }

    // Send the integer 1 or 0 to the server based on the value of sendOne
    int number = sendOne ? 1 : 0;
    send(client_fd, &number, sizeof(number), 0);
    std::cout << "sendOne: " << sendOne << ", number: " << number << std::endl;

    if (sendOne){
        ui->toggleSendValueButton->setText("Start Tracking");
        ui->toggleSendValueButton->setProperty("trackingActive", false);
    } else {
        ui->toggleSendValueButton->setText("Stop Tracking");
        ui->toggleSendValueButton->setProperty("trackingActive", true);
    }
    // Toggle the value of sendOne
    sendOne = !sendOne;
    // Close the socket
    ::close(client_fd);
}