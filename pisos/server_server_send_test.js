var app = require('express')();
var http = require('http').createServer(app);
var io = require('socket.io')(http);

// Client path
app.get('/', function (req, res) {
	res.sendFile(__dirname + '/public_server_send_test/index.html');
});

io.on('connection', function (socket) {
	console.log('NEW CONN: ' + socket.id);

	// Bind other events
	socket.on('disconnect', function () {
		console.log('DISCONN: ' + socket.id);
	});

	// Client is not sending anything else to the server
	// Client is receiving ONLY
});

http.listen(8000, function () {
	console.log('listening on *:8000');
	setup();
	runSim();
});

// Infinite loop using a timer
// This is where we set up a simple simulation environment
// Using simulation rate of 10hz
function runSim() {
	var time = 0;
	var delta = 1;
	var update_ms = 10;
	var intervalId = setInterval(function () {
		// console.log('Simulating time=' + time);
		time += delta;
		simulate(delta);
		senddata();
	}, update_ms);
}

// Simple planetary simulation where the origin (0, 0) is a mass
var center_mass = 10000;

// a = -GM/r^2
var GM = center_mass * 0.1;
var posx = [];
var posy = [];
var vx = [];
var vy = [];

function addBody(x, y, v_x, v_y) {
	posx.push(x);
	posy.push(y);
	vx.push(v_x);
	vy.push(v_y);
}

function setup() {
	addBody(50, 0, 0, -Math.sqrt(GM / 50));
	addBody(100, 0, 0, -Math.sqrt(GM / 100));
	addBody(150, 0, 0, -Math.sqrt(GM / 150));
	addBody(200, 0, 0, -Math.sqrt(GM / 200));

	addBody(50, 0, 0, -Math.sqrt(GM / 50) * 1.1);
	addBody(100, 0, 0, -Math.sqrt(GM / 100) * 1.1);
	addBody(150, 0, 0, -Math.sqrt(GM / 150) * 1.1);
	addBody(200, 0, 0, -Math.sqrt(GM / 200) * 1.1);
}

function simulate(dt) {
	// For each body, update
	for (var i = 0; i < posx.length; i++) {

		// Distance to center square
		var r2 = posx[i] * posx[i] + posy[i] * posy[i];

		// calculate acceleration to the center
		var acc_mag = -GM / r2;
		var theta = Math.atan2(posy[i], posx[i]);
		
		// Increment velocity
		vx[i] += acc_mag * Math.cos(theta) * dt;
		vy[i] += acc_mag * Math.sin(theta) * dt;

		// Increment position
		posx[i] += vx[i] * dt;
		posy[i] += vy[i] * dt;
	}
}

function senddata() {
	io.sockets.emit('simupdate', {
		p_x: posx,
		p_y: posy,
	});
}