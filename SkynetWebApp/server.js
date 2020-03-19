// Use Express as app, then set resources directory (static files)
let express = require('express');
let app = express();
app.use(express.static('public'))

// Http server and socket io
const SERVERPORT = 80;
let server = app.listen(SERVERPORT);
let io = require('socket.io')(server);

// Set up connections when socket connects
io.on('connection', (socket) => {

  // Receiving data from Python program
  socket.on('PY_IMG_DATA', (imageData) => {
    socket.broadcast.emit('SRV_IMG_DATA', imageData);
  });
});

