CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

TARGETS = chaos-emulator sender receiver

all: $(TARGETS)

chaos-emulator: src/ChaosEmulator.cpp src/ChaosEngine.cpp src/Statistics.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

sender: src/Sender.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

receiver: src/Receiver.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(TARGETS) *.o

run-receiver: receiver
	./receiver

run-emulator: chaos-emulator
	./chaos-emulator 20 100 50 0

run-sender: sender
	./sender

.PHONY: all clean run-receiver run-emulator run-sender
