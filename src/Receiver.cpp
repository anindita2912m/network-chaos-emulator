#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int serverSocket;
    char buffer[BUFFER_SIZE];

    serverSocket = socket(AF_INET, SOCK_DGRAM, 0);

    if (serverSocket < 0) {
        std::cerr << "Error creating socket.\n";
        return 1;
    }

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT);

    if (bind(serverSocket,
             (struct sockaddr*)&serverAddress,
             sizeof(serverAddress)) < 0) {
        std::cerr << "Error binding socket.\n";
        close(serverSocket);
        return 1;
    }

    std::cout << "UDP Receiver listening on port "
              << PORT << "...\n";

    while (true) {
        memset(buffer, 0, BUFFER_SIZE);

        sockaddr_in clientAddress{};
        socklen_t clientLength = sizeof(clientAddress);

        int bytesReceived = recvfrom(
            serverSocket,
            buffer,
            BUFFER_SIZE - 1,
            0,
            (struct sockaddr*)&clientAddress,
            &clientLength
        );

        if (bytesReceived < 0) {
            std::cerr << "Error receiving packet.\n";
            continue;
        }

        buffer[bytesReceived] = '\0';

        std::cout << "Received: " << buffer << std::endl;
    }

    close(serverSocket);
    return 0;
}
