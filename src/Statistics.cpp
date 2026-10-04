#include "Statistics.h"
#include <iostream>
#include <iomanip>

Statistics::Statistics()
    : totalPackets(0),
      forwardedPackets(0),
      droppedPackets(0) {
}

void Statistics::packetReceived() {
    totalPackets++;
}

void Statistics::packetForwarded() {
    forwardedPackets++;
}

void Statistics::packetDropped() {
    droppedPackets++;
}

void Statistics::displayResults() const {
    double lossPercentage = 0.0;

    if (totalPackets > 0) {
        lossPercentage =
            (static_cast<double>(droppedPackets) / totalPackets) * 100.0;
    }

    std::cout << "\n========== CHAOS TEST RESULTS ==========\n";

    std::cout << "Total Packets : "
              << totalPackets << '\n';

    std::cout << "Forwarded     : "
              << forwardedPackets << '\n';

    std::cout << "Dropped       : "
              << droppedPackets << '\n';

    std::cout << std::fixed << std::setprecision(2);

    std::cout << "Actual Loss   : "
              << lossPercentage << "%\n";

    std::cout << "========================================\n";
}
