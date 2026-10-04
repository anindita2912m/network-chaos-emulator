
#include <iostream>
#include <cstring>
#include <csignal>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "ChaosEngine.h"
#include "Statistics.h"

#define EMULATOR_PORT 8081
#define RECEIVER_PORT 8080
#define BUFFER_SIZE 1024

Statistics* statsPtr = nullptr;

void handleSignal(int signal) {
    if (signal == SIGINT && statsPtr != nullptr) {
        statsPtr->displayResults();
        exit(0);
    }
}

int main(int argc, char* argv[]) {
    double lossRate = 20.0;
int latencyMs = 100;
int jitterMs=0;

if (argc >= 2) {
    lossRate = std::stod(argv[1]);
}

if (argc >= 3) {
    latencyMs = std::stoi(argv[2]);
}
if (argc >=4){
	jitterMs=std::stoi(argv[3]);
}
    int emulatorSocket;

    emulatorSocket = socket(AF_INET, SOCK_DGRAM, 0);

    if (emulatorSocket < 0) {
        std::cerr << "Error creating socket.\n";
        return 1;
    }

    sockaddr_in emulatorAddress{};
    emulatorAddress.sin_family = AF_INET;
    emulatorAddress.sin_addr.s_addr = INADDR_ANY;
    emulatorAddress.sin_port = htons(EMULATOR_PORT);

    if (bind(emulatorSocket,
             (struct sockaddr*)&emulatorAddress,
             sizeof(emulatorAddress)) < 0) {
        std::cerr << "Error binding emulator socket.\n";
        close(emulatorSocket);
        return 1;
    }

    sockaddr_in receiverAddress{};
    receiverAddress.sin_family = AF_INET;
    receiverAddress.sin_port = htons(RECEIVER_PORT);
    receiverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    ChaosEngine chaos(lossRate, latencyMs, jitterMs);
    Statistics statistics;
	statsPtr = &statistics;
	signal(SIGINT, handleSignal);
    char buffer[BUFFER_SIZE];

    std::cout << "Chaos Emulator running...\n";
    std::cout << "Packet Loss: "
              << chaos.getLossRate() << "%\n";
    std::cout << "Latency: "
              << chaos.getLatency() << " ms\n";
    std::cout << "Jitter:" 
	      << chaos.getJitter() << " ms\n";

    while (true) {
        sockaddr_in senderAddress{};
        socklen_t senderLength = sizeof(senderAddress);

        int bytesReceived = recvfrom(
            emulatorSocket,
            buffer,
            BUFFER_SIZE - 1,
            0,
            (struct sockaddr*)&senderAddress,
            &senderLength
        );

        if (bytesReceived < 0) {
            std::cerr << "Error receiving packet.\n";
            continue;
        }

        buffer[bytesReceived] = '\0';
	statistics.packetReceived();
        if (chaos.shouldDropPacket()) {
	statistics.packetDropped();
            std::cout << "DROPPED: "
                      << buffer << std::endl;
            continue;
        }

        chaos.applyLatency();

        sendto(
            emulatorSocket,
            buffer,
            bytesReceived,
            0,
            (struct sockaddr*)&receiverAddress,
            sizeof(receiverAddress)
        );
	statistics.packetForwarded();
        std::cout << "FORWARDED: "
                  << buffer << std::endl;
    }

    close(emulatorSocket);
    return 0;
}
