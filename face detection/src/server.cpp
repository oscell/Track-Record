#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>

int main() {
    int server_fd, client_fd, addr_len;
    struct sockaddr_in server_addr, client_addr;
    int opt = 1;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_fd, 3);

    std::cout << "Server running on IP: " << inet_ntoa(server_addr.sin_addr) << ", Port: " << ntohs(server_addr.sin_port) << std::endl;

    addr_len = sizeof(client_addr);
    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, (socklen_t *)&addr_len);

    // Print the client connection information
    std::cout << "Client connected: IP " << inet_ntoa(client_addr.sin_addr) << ", Port " << ntohs(client_addr.sin_port) << std::endl;

    while (true) {
        int number;
        std::cout << "Enter 0 or 1: ";
        std::cin >> number;

        send(client_fd, &number, sizeof(number), 0);
    }

    close(client_fd);
    close(server_fd);

    return 0;
}
