# TRexController

Remotely control the T-REG-HMI Unity app.

This comes in two parts:
* A simple webpage with some controls (the `controller` subdirectory).
* A websockets server (the `websockets` subdirectory).

### The controller webapp

Basically the code is all in `controller/index.html`.   If you are running locally you can just point your browser to this using the `file://` protocol, or you can serve using your http server of choice (e.g. from the `controller/` directory you can do `python3 -m http.server`.

### Websockets server

This uses the excellent open source websockets server https://github.com/Theldus/wsServer as a git submodule.

After cloning this repo, run the commands:
```
git submodule init
git submodule update
```
Then change to the `websockets/wsServer` directory and run:
```
make
```
and then do
```
cd ..
gcc -I wsServer/include -std=c99 -pthread -pedantic server.c -o server wsServer/libws.a
```
You can then run the executable
```
./server
```

## Deploying this on an Azure VM

* Get a Linux VM.
* In the Azure portal, for this VM, open "Network Settings", and add inbound port rules, opening ports 9010 and 8080.
* Open two terminals, connecting to the  via ssh key pair.
* `sudo apt install make` and `sudo apt install build-essential`.
* Clone this repo, and `cd TRexController/websockets`.
* `git submodule init; git submodule update`.
* `cd wsServer; make; cd ..`
* Edit `server.c` to set "host" to "0.0.0.0".
* `gcc -I wsServer/include -std=c99 -pthread -pedantic server.c -o server wsServer/libws.a`
* Run the websockets server with `./server`.
* In the other terminal, `cd TRexController/controller`.
* Edit `index.html` to set the websockets address to `ws://{ip_address_of_vm}:9010` (you can see the IP address from the "overview" page of the VM in the Azure portal.
* Run `python3 -m http.server 8080`
* You should then be able to point a web browser (e.g. on your phone) to `http://{ip_address_of_vm}:8080` - note that this may be blocked by some WiFi.
* If all works, you should see the controller app, and the terminal running the websockets server should display messages as you move the joysticks and press buttons.
  

