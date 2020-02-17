// Use Express as app, then set resources directory (static files)
let express = require('express');
let app = express();
app.use(express.static(__dirname + 'public'))

// Set app to map root to index.html
app.get('/', function (req, res) {
  res.sendFile(__dirname + '/public/index.html');
});

// Http server and socket io
let server = require('http').Server(app);
let io = require('socket.io')(server);

// Http server set up connection
const LOCALHOST_PORT = 80;
server.listen(LOCALHOST_PORT, () => {
  console.log('Listening on port: ' + LOCALHOST_PORT);
})

// Set up connections when socket connects
io.on('connection', (socket) => {

  // Receiving data from Python program
  socket.on('PY_IMG_DATA', (imageData) => {
    socket.broadcast.emit('SRV_IMG_DATA', 'data:image/png;base64,' + imageData.toString());
  });
});

