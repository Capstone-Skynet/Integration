# PISOS
Raspberry PI Socket.io Server

## Requirements

Run this `npm` command to install the necessary packages

```shell
npm install
```

## Usage

Currently there are two tests written to test the usability of a websocket server for WLAN communications.

1. Draw Test
2. Server Send Test

Both opens up a node.js server, and serves the client an *index.html* file.

### Draw Test

The **Draw test** is a simple "shared canvas" with many client to many client communication. Each connected client can send and receive data mediated by the host server.

To run the server, execute

```shell
node server_draw_test
```

To connect to the server as a client, type in the IP address of the host server followed by port 8000 (`:8000`).

### Server Send Test

The **Server send test** is a simple gravity simulator running on the server (with no rendering). The data from the physics simulation is sent via socket to the client. This test demonstrates the one-to-many communication where all connected clients are rendering the same data (almost) in-sync.

To run the server, execute

```shell
node server_server_send_test
```

To connect to the server as a client, type in the IP address of the host server followed by port 8000 (`:8000`).