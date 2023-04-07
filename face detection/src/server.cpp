#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <thread>
#include <vector>
#include <atomic>

std::atomic<int> shared_number;

void handle_client(int client_fd) {
    while (true) {
        int number;
        int recv_status = recv(client_fd, &number, sizeof(number), 0);

        if (recv_status <= 0) {
            std::cerr << "Client disconnected" << std::endl;
            close(client_fd);
            break;
        }

        std::cout << "Received from client: " << number << std::endl;
        shared_number.store(number);

        int current_number = shared_number.load();
        int send_status = send(client_fd, &current_number, sizeof(current_number), 0);
        if (send_status == -1) {
            perror("send");
        } else {
            std::cout << "Sent to client: " << current_number << std::endl;
        }
    }
}



int main() {
    int server_fd;
    struct sockaddr_in server_addr;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_fd, 5);

    char ip_buffer[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &server_addr.sin_addr, ip_buffer, INET_ADDRSTRLEN);
    std::cout << "Server is running on IP: " << ip_buffer << " Port: " << ntohs(server_addr.sin_port) << std::endl;

    shared_number.store(-1);

    std::vector<std::thread> client_threads;

    while (true) {
        struct sockaddr_in client_addr;
        socklen_t client_addr_size = sizeof(client_addr);

        int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_size);
        std::cout << "Client connected" << std::endl;

        client_threads.push_back(std::thread(handle_client, client_fd));
    }

    for (auto &thread : client_threads) {
        thread.join();
    }

    close(server_fd);

    return 0;
}
