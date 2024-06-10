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
