# Test Plan

| Test | Loss | Latency | Jitter | Bandwidth | Expected |
|---|---:|---:|---:|---:|---|
| Normal | 0% | 0 ms | 0 ms | 0 | All packets forwarded |
| Low latency | 0% | 50 ms | 0 ms | 0 | All packets delayed |
| Packet loss | 10% | 0 ms | 0 ms | 0 | Some packets dropped |
| High latency | 0% | 200 ms | 0 ms | 0 | Significant delay |
| Jitter | 0% | 100 ms | 50 ms | 0 | Variable delay |
| Combined | 20% | 100 ms | 50 ms | 0 | Loss + delay + jitter |
| Bandwidth | 0% | 0 ms | 0 ms | 256 kbps | Rate-limited forwarding |

Because packet loss is randomized, actual loss may differ from configured loss for a small sample.
