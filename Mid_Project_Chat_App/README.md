# P2P Chat Application

A peer-to-peer chat application written in C that allows multiple clients to connect and communicate with each other in a decentralized network.

## Features

- **Peer-to-peer architecture**: No central server required
- **Multiple connections**: Support up to MAX_PEER simultaneous connections
- **Thread-safe**: Uses mutex locks for concurrent connection handling
- **Real-time messaging**: Send and receive messages instantly
- **Connection management**: List, connect, and terminate peer connections
- **Graceful shutdown**: Proper cleanup of resources on exit

## Usage
### Compilation
```bash
make
```
### Starting the Application

```bash
./main <port>
```

Example:
```bash
./main 8080
```

### Available Commands

Once the application is running, you can use the following commands:

| Command | Shortcut | Description |
|---------|----------|-------------|
| `help` | `1` | Display command list |
| `myip` | `2` | Show this application's IP address |
| `myport` | `3` | Show this application's listening port |
| `connect <ip> <port>` | `4` | Connect to a remote peer |
| `list` | `5` | List all active connections |
| `terminate <id>` | `6` | Close a connection by ID |
| `send <id> <msg>` | `7` | Send message to a peer |
| `exit` | `8` or `q` | Quit the application |

### Command Examples

```bash
# Check your IP address
myip

# Check your listening port
myport

# Connect to a peer
connect 192.168.1.100 8081

# List all connections
list

# Send a message to peer with ID 0
send 0 Hello, World!

# Terminate connection with peer ID 1
terminate 1

# Exit the application
exit
```

## Architecture

### Main Components

- **Main Thread**: Handles user input and command processing
- **Connection Thread**: Listens for incoming peer connections
- **Receive Threads**: One per peer connection, handles incoming messages

### Thread Safety

The application uses a mutex lock (`peer_lock`) to protect shared data structures:
- Peer list modifications
- Connection count updates
- Socket operations

### Connection Flow

1. **Incoming Connections**:
   - Connection thread listens on the specified port
   - Accepts new connections when available
   - Creates a receive thread for each new peer

2. **Outgoing Connections**:
   - User initiates connection via `connect` command
   - Application creates socket and connects to remote peer
   - Creates a receive thread for the new connection

3. **Message Handling**:
   - Each peer has a dedicated receive thread
   - Messages are received and logged in real-time
   - Thread terminates when peer disconnects

## Configuration

Edit the following constants in `utils.h`:

```c
#define MAX_PEER 10              // Maximum number of simultaneous connections
#define TIME_SLEEP 100000        // Main loop sleep time (microseconds)
#define DEFAULT_LOG_PATH "log.txt"  // Log file path
```

## Logging

The application logs all activities to `log.txt` by default. Log levels include:
- **DEBUG**: Detailed diagnostic information
- **INFO**: General informational messages
- **WARNING**: Warning messages for non-critical issues
- **ERROR**: Error messages for critical failures

## Error Handling

The application handles various error conditions:
- Invalid port numbers
- Connection failures
- Socket errors
- Maximum peer limit reached
- Invalid command syntax


