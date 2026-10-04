#include "ChaosEngine.h"

#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

ChaosEngine::ChaosEngine(double loss, int latency, int jitter)
    : lossRate(loss),
      latencyMs(latency),
      jitterMs(jitter) {
    std::srand(std::time(nullptr));
}

bool ChaosEngine::shouldDropPacket() {
    double randomValue =
        static_cast<double>(std::rand()) / RAND_MAX * 100.0;

    return randomValue < lossRate;
}

void ChaosEngine::applyLatency() {
    int actualDelay = latencyMs;

    if (jitterMs > 0) {
        int variation =
            (std::rand() % (2 * jitterMs + 1)) - jitterMs;

        actualDelay += variation;
    }

    if (actualDelay < 0) {
        actualDelay = 0;
    }

    std::this_thread::sleep_for(
        std::chrono::milliseconds(actualDelay)
    );
}

double ChaosEngine::getLossRate() const {
    return lossRate;
}

int ChaosEngine::getLatency() const {
    return latencyMs;
}

int ChaosEngine::getJitter() const {
    return jitterMs;
}
