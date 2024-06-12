# TRexController

Remotely control the T-REG-HMI Unity app.

This has two components:
* A simple webpage with some controls (implemented in `src/public/index.html`).
* A websockets server (implemented in `src/index.js`, which also acts as the http server for the webpage described above).

### Running locally

* Ensure that the WebSocket connection string in `src/public/index.html` is set to `wss://localhost:8080`.
* If you don't already have them, install `node` and `npm`.   Then do
```
cd src
npm install
node index.js
```


## Deploying this as an Azure WebApp

* Choose a name for your Azure webapp (e.g. "t-reg-control").
* Set the WebSocket connection string in `src/public/index.html` to `wss://{webapp_name}.azurewebsites.net`.
* Save, commit, and push this file.   A GitHub Action will then build and push the docker image.
* Create a container-based WebApp via the Azure portal, and point it to the relevant image on dockerhub.
* In your client app, also set the WebSocket connection string to `wss://{webapp_name}.azurewebsites.net`.

# Thoughts on generalising to other apps with separate controller+visualization.

Custom bits of code are:
* the code for controller app in `index.html` and `joy.js`.
* the websockets connection string in `index.html` - this could be inserted programatically if we were to have a "setup-your-own-apps" script.
* logic in `src/index.js` for sending messages to different clients, based on a handshake message (in this case "TREG").   We could design a protocol for this.
* The GitHub Action defined in `.github/workflows/build-docker.yaml` has the name of the docker image.  (The Dockerhub username and password are repository secrets).

We could think about something like Pulumi/Terraform to auto-deploy an Azure WebApp.   Could also potentially use an API to auto-generate a QR code that could be displayed on the "visualization" app, to point the user to the "controller" app.

