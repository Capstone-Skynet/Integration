# SkynetWebApp

A js server-client webapp for the base station.

## Requirements

This server runs on Node.js. Please ensure Node.js version 13 is installed. Note that newer versions of Node.js should work but is not tested.

## Packages

The `server.js` requires express and socket.io.

    npm install express
    npm install --save socket.io

The `client.py` requires the socket.io client library

    pip install "python-socketio[client]"

## Usage

Turn on the server first

    node server

Then run the python client

    python client.py

And open the webapp in the browser according to your set port (Default 80).

    http://localhost:80
