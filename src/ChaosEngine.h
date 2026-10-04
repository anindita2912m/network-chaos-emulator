#ifndef CHAOS_ENGINE_H
#define CHAOS_ENGINE_H

class ChaosEngine {
private:
    double lossRate;
    int latencyMs;
    int jitterMs;

public:
    ChaosEngine(double loss, int latency, int jitter);

    bool shouldDropPacket();
    void applyLatency();

    double getLossRate() const;
    int getLatency() const;
    int getJitter() const;
};

#endif
