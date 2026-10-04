# Network Latency & Packet-Loss Chaos Emulator

A Linux-based C++ UDP network chaos emulator developed for system programming and networking experimentation.

## Features

- UDP sender and receiver
- Configurable packet loss
- Configurable fixed latency
- Configurable jitter
- Optional bandwidth limitation
- Packet forwarding through an emulator
- Packet statistics and throughput
- Command-line configuration
- Linux socket programming
- Makefile-based build

## Architecture

UDP Sender -> Chaos Emulator -> UDP Receiver

## Build

```bash
make
```

## Run

Open three terminals in the project directory.

### Terminal 1
```bash
./receiver
```

### Terminal 2
```bash
./chaos-emulator 20 100 50 0
```

Arguments:

```text
loss_percent latency_ms jitter_ms bandwidth_kbps
```

Use `0` for unlimited bandwidth.

Example:
```bash
./chaos-emulator 10 50 20 256
```

### Terminal 3
```bash
./sender
```

After the sender finishes, press `Ctrl+C` in the emulator terminal to display statistics.

## Example

```text
========== NETWORK CHAOS EMULATOR ==========
Packet Loss : 20%
Latency     : 100 ms
Jitter      : 50 ms
Bandwidth   : Unlimited
Listening   : UDP port 8081
============================================
```

## Project Structure

```text
network-chaos-emulator/
├── src/
│   ├── main.cpp
│   ├── Sender.cpp
│   ├── Receiver.cpp
│   ├── ChaosEngine.cpp
│   ├── ChaosEngine.h
│   ├── Statistics.cpp
│   └── Statistics.h
├── tests/
├── logs/
├── results/
├── docs/
├── Makefile
├── README.md
└── .gitignore
```

## Technology

- C++
- Linux
- POSIX UDP sockets
- Threads/timing
- GNU Make
- Git/GitHub
