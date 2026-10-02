# KVCC

A tiny Redis-like key-value cache server written in pure C, built as a staged
learning project: start with a blocking single-client echo loop, work up to
an `epoll`-based multi-client reactor, then swap the I/O layer for `io_uring`
and benchmark the difference directly.

## Protocol

Simple text protocol, testable with `nc`:

```
SET key value\r\n   -> +OK\r\n
GET key\r\n          -> $value\r\n   or  $-1\r\n (missing)
DEL key\r\n          -> :1\r\n / :0\r\n
PING\r\n             -> +PONG\r\n
STATS\r\n            -> connection count / ops-per-second / hit rate
```

## Roadmap

| Stage | What |
|---|---|
| M0 | Blocking socket, one client at a time (echo only) |
| M1 | Real hash table wired in: SET/GET/DEL/PING |
| M2 | `epoll`-based multi-client reactor (single thread, non-blocking) — the baseline |
| M3 | Benchmark client (ops/sec, p50/p99 latency) |
| M4 | Same protocol + hash table, I/O loop rewritten with `io_uring` — re-run M3's benchmark and compare |
| M5 | `SO_REUSEPORT` + sharded/lock-free hash table across multiple reactor threads |
| M6 | XDP/eBPF connection-rate prefilter |
| M7 | Real RESP compatibility so `redis-cli`/`redis-benchmark` can talk to it |

Currently at **M0**.

## Build

```sh
cmake -S . -B build
cmake --build build
./build/kvcc
```

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md) for commit/PR conventions.
