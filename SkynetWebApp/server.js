var app = require('express')();
var server = require('http').Server(app);
var io = require('socket.io')(server);
var fs = require ('fs');
var path = require ('path');

server.listen(80);
// WARNING: app.listen(80) will NOT work here!

app.get('/', function (req, res) {
  res.sendFile(__dirname + '/index.html');
});

io.on('connection', function (socket) {
  socket.emit('news', { hello: 'world' });
  socket.on('my other event', function (data) {
    //socket.emit('pyimg2webapp', "wtf");
    console.log(data);
  });
 
  // image sending sourced from https://gist.github.com/companje/b95e735650f1cd2e2a41
  var i = 1;
  socket.on('image_callcheck', function () {
    var f_name = __dirname + '/Images/' + i.toString() + '.jpg'; 
    fs.readFile(f_name, function(err, data){
      socket.emit('imageConversionByServer', "data:image/png;base64,"+ data.toString("base64"));
    });
    if (i == 10) 
      i = 1;
    else
      i++;
  });

  // Calling the python script to receive image.
  socket.on('py_img_receive', function(data) {
    socket.broadcast.emit('pyimg2webapp', "data:image/png;base64," + data.toString());
  });

  socket.on('pytest', function(data) {
    console.log(data)
  });
});

