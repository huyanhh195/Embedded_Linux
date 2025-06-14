# IPC SIGNAL

## How to run
1. Comile 
```bash
make
```
Which will create file bin in each folder
2. Run with format
- ip4_stream
```bash
./ip4_stream/server 8554
./ip4_stream/client 127.0.0 8554
```
with 127.0.0 is the ip, 8554 is port
- ip4_datagram
```bash
./ip4_datagram/server 8554
./ip4_datagram/client 127.0.0 8554
```
with 127.0.0 is the ip, 8554 is port
- unix_stream
```bash
./unix_stream/server
./unix_stream/client
```
- unix_datagram
```bash
./unix_datagram/server
./unix_datagram/client
```