let app = require('express')();
let server = require('http').Server(app);
let io = require('socket.io')(server);

// var fs = require('fs');

const LOCALHOST_PORT = 80;

server.listen(LOCALHOST_PORT, () => {
  console.log('Listening on port: ' + LOCALHOST_PORT);
})
// WARNING: app.listen(80) will NOT work here!

app.get('/', function (req, res) {
  res.sendFile(__dirname + '/public/index.html');
});

io.on('connection', (socket) => {
  // Set up connections when socket connects

  // Receiving data from Python program
  socket.on('PY_IMG_DATA', (imageData) => {
    socket.broadcast.emit('SRV_IMG_DATA', 'data:image/png;base64,' + imageData.toString());
  });
});

