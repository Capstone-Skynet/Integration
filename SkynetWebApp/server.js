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

  // Receiving image from Python program
  socket.on('PY_IMG_DATA', (imageData) => {
    socket.broadcast.emit('SRV_IMG_DATA', imageData);
  });

  // Receiving ml result from Python program
  socket.on('PY_ML_RESULT', (result) => {
    console.log(result);

  // Changing settings from webapp
  //gs_threshold, gs_mode
  socket.on('WEB2SRV_threshold_val', (value) => {
    console.log("Threshold Value Updated to " + value)
    socket.broadcast.emit('gs_threshold', value);
  });

  socket.on('WEB2SRV_detect_obj_on', (value) => {
    console.log(value + " detection turned on");
    socket.broadcast.emit('gs_mode', value);
  });

});

