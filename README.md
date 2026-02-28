# IP Messenger (TCP Socket Chat Application)

A basic TCP client-server chat application using the `select()` system call.

## Build and Run (using Docker)

Since the project uses Docker, you do not need gcc or a C compiler installed on your local machine. You only need Docker installed.

### 1. Build the images

```bash
docker compose build
```

### 2. Start the Server

```bash
docker compose up -d server
```

### 3. Connect a Client

Open a new terminal and run:

```bash
docker compose run client <client_name> server
```

_(Example: `docker compose run client aryan server`)_

Repeat this step in additional terminals with different client names to simulate multiple users.

## Client Commands

Once the client is running, you can use the following commands:

1. **`LIST`**: Gives a list of all connected clients.
2. **`CONNECT <client_name>`**: Connects your client with another specified client from the list.
   _(Note: You must CONNECT before sending a private message to another client)._
3. **`ALL <message>`**: Sends a broadcast message to every client connected to the server.
   _(Note: No need to run CONNECT, just type `ALL message...` to send to everyone)._
4. **`EXIT`**: Disconnects from the server and terminates the client.

## Local Cleanup

If you need to stop and clean up the Docker containers:

```bash
docker compose down
```
