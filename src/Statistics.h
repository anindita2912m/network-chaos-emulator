#ifndef STATISTICS_H
#define STATISTICS_H

class Statistics {
private:
    int totalPackets;
    int forwardedPackets;
    int droppedPackets;

public:
    Statistics();

    void packetReceived();
    void packetForwarded();
    void packetDropped();

    void displayResults() const;
};

#endif
