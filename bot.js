'use strict';

const net = require('net');

let socket = net.connect(12345, 'localhost');

socket.on('connect', function() {
	console.log('CONNECT');

	let buffer = new Buffer(0);
	socket.on('data', function(p_buffer) {
		buffer = Buffer.concat([buffer, p_buffer]);

		if(buffer.length > 4) {
			let type = buffer.readInt32LE(0);
			console.log('type: ' + type);
			console.log(buffer);
		}
	});

	socket.on('error', function(p_error) {
		console.log('ERROR');
		console.log(p_error.stack);
	});

	socket.on('close', function() {
		console.log('CLOSE');
	});

	socket.write(new Buffer([0x01, 0x02, 0x03, 0x04]));
});