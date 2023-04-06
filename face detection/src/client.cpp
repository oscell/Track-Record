#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <chrono>
#include <thread>
#include <signal.h>
#include <cstdlib>

pid_t run_executable(const char *executable) {
    pid_t pid = fork();

    if (pid == 0) {
        execl(executable, executable, nullptr);
        perror("execl");
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    return pid;
}

int main() {
    int client_fd;
    struct sockaddr_in server_addr;

    client_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(8080);

    connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    pid_t running_executable_pid = -1;

    while (true) {
        int number;
        recv(client_fd, &number, sizeof(number), 0);
        std::cout << "Received: " << number << std::endl;

        if (number == 0) {
            if (running_executable_pid != -1) {
                kill(running_executable_pid, SIGTERM);
                std::cout << "Terminated executable" << std::endl;
                running_executable_pid = -1;
            }
        } else if (number == 1) {
            if (running_executable_pid == -1) {
                // Set the path to the executable located in the same directory as the client
                const char *executable_path = "./facedet";
                running_executable_pid = run_executable(executable_path);
                std::cout << "Started executable" << std::endl;
            } else {
                std::cout << "Executable already running" << std::endl;
            }
        }

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    close(client_fd);

    return 0;
}
