# SkynetWebApp

A node.js server-client webapp for the base station.

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

And open the webapp in the browser

    http://localhost