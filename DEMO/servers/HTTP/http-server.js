/**
 * A simple express server to test if the generated files work.
 */

const express = require('express');
const bodyParser = require('body-parser');
const server = express();
const path = require('path');

server.use(bodyParser.json());
server.use(bodyParser.urlencoded({ extended: true }));

server.get('/', (req, res) => {
	res.status(200).sendFile(path.posix.resolve('./index.html'));	
});

server.get('/sayhi', (req, res) => {
	res.status(200).sendFile(path.posix.resolve('./sayhi.html'));
});

server.get('/style.css', (req, res) => {
	res.status(200).sendFile(path.posix.resolve('./style.css'));
});

server.post('/sayhi', (req, res) => {
	res.status(200).send(`Hi, ${req.body.username}!`);
});

server.listen(80, () => console.log('HTTP server listening on port 80...'));
