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
    int client_fd, server_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_fd, 1);

    std::cout << "Listening on port 8080" << std::endl;

    

    pid_t running_executable_pid = -1;

    while (true) {
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
        int number = -1;
        int recv_status = recv(client_fd, &number, sizeof(number), 0);

        if (recv_status <= 0) {
            std::cerr << "GUI disconnected" << std::endl;
        }

        std::cout << "Client received: " << number << std::endl;

        if (number == 1) {
            std::cout << "Received: " << number << std::endl;

            if (running_executable_pid == -1) {
                running_executable_pid = run_executable("./facedet");
                std::cout << "Started executable" << std::endl;
            } else {
                std::cout << "Executable already running" << std::endl;
            }
        } else if (number == 0) {
            std::cout << "Received: " << number << std::endl;

            if (running_executable_pid != -1) {
                kill(running_executable_pid, SIGTERM);
                std::cout << "Terminated executable" << std::endl;
                running_executable_pid = -1;
            } else {
                std::cout << "Executable not running" << std::endl;
            }
        }

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    close(client_fd);
    close(server_fd);

    return 0;
}
