var app = require('express')();
var http = require('http').createServer(app);
var io = require('socket.io')(http);

app.get('/', function (req, res) {
	res.sendFile(__dirname + '/public_draw_test/index.html');
});

io.on('connection', function (socket) {
	console.log('NEW CONN: ' + socket.id);

	// Bind other events
	socket.on('disconnect', function () {
		console.log('DISCONN: ' + socket.id);
	});

	socket.on('drawEvent', function(data) {
		console.log(data);
		socket.broadcast.emit('drawEvent', data);
	});
});

http.listen(8000, function () {
	console.log('listening on *:8000');
});