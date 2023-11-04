# minitalk

## Overview
Interprocess communication program
Send message from Client to Server
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
./client 12345 Hello World! 
```

## License
[MIT](https://github.com/yuto1009/minitalk/blob/master/LICENSE)
