# Simple TCP Reverse Proxy

A simple TCP reverse proxy written in C++

## Building

Supported OSs:
* Windows - ✅
* Linux - ❌
* MacOS - ❌

Cmake build files are included in the server and client directories.

## How to use

1. Run the proxy server executable in a remote server
2. Run the proxy client executable with the proxy server adress and the desired port to "remotify" on the local host machine (the machine running the application remote clients will connect to)
   ```bash
   client.exe <proxy address> <host port>
   ```
3. Use the port the client prints with the address of the proxy server and connect from remote clients

## Adjustments
* The proxy server and client' thread count can be modified via the ```config.cpp``` file

## Notes
* Thread adjustment has only been tested on the proxy server.
* Remote clients' IP is hidden from the proxy client and the local host.

## Behind the scenes
When the proxy client connects to the proxy server the server opens a port at its end and sends it to the client. When a remote clients connects to that port it sends a notificaion to the proxy client which creates a local socket that connects to the local host. Now, when the remote client sends data the proxy server sends it to the client and from there is it sent to the local host from the local socket and vice versa.

## Todo
* Test the client thread count adjustment (fix data race)

## License
