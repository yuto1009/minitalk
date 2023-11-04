# minitalk
![gif](https://github.com/yuto1009/minitalk/blob/master/minitalk_video.gif)
## Overview
A user can message from Client to Server.
This is a simple interprocess communication program using Unix signals.
## Requirement
- macOS
- Clang
## Usage
At first, compile as follows:
```
make
./server
```
The server program will print process ID
Execute the client program with the process ID to send messages:
```
./client 12345 Hello World
```

## License
[MIT](https://github.com/yuto1009/minitalk/blob/master/LICENSE)
