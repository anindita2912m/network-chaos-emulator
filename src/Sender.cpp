#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8081

int main() {
    int clientSocket;

    clientSocket = socket(AF_INET, SOCK_DGRAM, 0);

    if (clientSocket < 0) {
        std::cerr << "Error creating socket.\n";
        return 1;
    }

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    std::cout << "UDP Sender started.\n";

    for (int i = 1; i <= 10; i++) {
        std::string message = "Packet " + std::to_string(i);

        sendto(
            clientSocket,
            message.c_str(),
            message.length(),
            0,
            (struct sockaddr*)&serverAddress,
            sizeof(serverAddress)
        );

        std::cout << "Sent: " << message << std::endl;

        usleep(500000);
    }

    close(clientSocket);

    std::cout << "Sender finished.\n";

    return 0;
}
