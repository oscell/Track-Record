#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QMessageBox"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
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
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(8080);
    
    if (::connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection to server failed");
        ::close(client_fd);
        return;
    }


    // Send the integer 1 to the server
    int number = 1;
    send(client_fd, &number, sizeof(number), 0);

    // Close the socket
    ::close(client_fd);

    // Show the message box
    QMessageBox msgBox;
    msgBox.setText("Button pressed, sent 1 to the server");
    msgBox.exec();
}

void MainWindow::on_terminateButton_clicked()
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
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(8080);
    
    if (::connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection to server failed");
        ::close(client_fd);
        return;
    }


    // Send the integer 0 to the server
    int number = 0;
    send(client_fd, &number, sizeof(number), 0);

    // Close the socket
    ::close(client_fd);

    // Show the message box
    QMessageBox msgBox;
    msgBox.setText("Button pressed, sent 0 to the server");
    msgBox.exec();
}