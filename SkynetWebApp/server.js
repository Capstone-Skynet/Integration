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

  socket.on('WEB2SRV_threshold_val', (value) => {
    console.log("Threshold Value Updated to " + value)
    socket.broadcast.emit('SRV2RPI_threshold_val', value);
  });

  socket.on('WEB2SRV_detect_obj_on', (value) => {
    console.log(value + " detection turned on");
    socket.broadcast.emit('SRV2RPI_detect_obj_on', value);
  });

  socket.on('WEB2SRV_detect_obj_off', (value) => {
    console.log(value + " detection turned off");
    socket.broadcast.emit('SRV2RPI_detect_obj_off', value);
  });
});

