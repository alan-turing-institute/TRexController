const express = require('express');
const http = require('http');
const WebSocket = require('ws');

const app = express();

// Serve static files or your web app
app.use(express.static('public'));

// Create HTTP server
const server = http.createServer(app);

// Create WebSocket server on top of HTTP server
const wss = new WebSocket.Server({ server });

// Map of clients with identifiers
const clients = new Map();


wss.on('connection', (ws) => {
  console.log('Client connected');

  ws.on('message', (message) => {
      console.log(`Received a message: ${message}`);
      // note "==" not "===" here to make comparison work
      if (message == "TREG") {
	  console.log("Identified TREG client");
	  const clientId = "TREG";
	  clients.set(clientId, ws);

	  ws.send(`Echo: ${message}`);
      } else {

	  if (clients.has("TREG")) {
	      console.log("sending message "+message+" to TREG");
	      clients.get("TREG").send(message);
	  }
      }

  });

  ws.on('close', () => {
      console.log('Client disconnected');
      for (let [key, clientWs] of clients) {
      if (clientWs === ws) {
        clients.delete(key);
        break;
      }
    }
  });
});

// Start the server
const PORT = process.env.PORT || 8080;
server.listen(PORT, () => {
  console.log(`Server is listening on port ${PORT}`);
});
