// Socket client
var socket;

function socketEmit(cmd, data) {
	if (socket === undefined) {
		console.error('Socket is not initialized.');
	}

	if (data === undefined) {
		socket.emit(cmd);
	} else {
		socket.emit(cmd, data);
	}
	socket.emit('nop');
}

function setupSocket(addr, port) {
	var url = 'http://' + addr + ':' + port;
	socket = io.connect(url);
	console.log('Connecting to ' + url);

	socket.on('drawEvent', drawEventHandler);
}

// p5 functions
function setup() {
	canvas = createCanvas(windowWidth, windowHeight, P2D);
	canvas.position(0, 0);
	resetBackground();

	// Socket
	setupSocket();
}

function resetBackground() {
	background(255);
	fill(0);
	textAlign(LEFT, BASELINE);
	textSize(10);
	text('Copyright 2019 (c) Muchen He', 10, 10);
}

function draw() {
	if (mouseIsPressed) {
		stroke(0);
		strokeWeight(5);
		line(mouseX, mouseY, pmouseX, pmouseY);

		socketEmit('drawEvent', {
			x: mouseX,
			y: mouseY,
			px: pmouseX,
			py: pmouseY
		});
	}
}

function drawEventHandler(data) {
	console.log(data);
}