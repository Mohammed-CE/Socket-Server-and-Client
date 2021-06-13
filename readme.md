# Storage Server Project 
### System Components
- Server.
- Client.
- Inter-Process-Communication ( Connection Oriented Protocol TCP ).

### Socket programming 

Socket programming is a way of connecting two nodes on a network to  communicate with each other. One socket(node) listens on a particular port for an IP, while the other socket reaches out to the other to form a connection. Server forms the listener socket while client reaches out to the server. 

### socket type:

In this project we used the SOCK_STREAM: TCP(reliable, connection oriented) .

### Client Process & Server Process:

1. #### server :
- Create a socket with the `socket()` system call.
- Bind the socket to an address (IP + port) using the `bind()` system call.
- Listen for connections with the `listen()` system call.
- Accept a connection with the `accept()` system call then create a thread for the client. This call typically blocks the connection until a client connects with the server.
- Send and receive data using the `read()` and `write()` system calls.


2. #### client :
- Create a socket with the `socket()` system call.
- Connect socket to the address of the server using the `connect()` system call.
- Send and receive data. There are a number of ways to do this, but the simplest way is to use the `read()` and `write()` system calls.

  
### Operation Types 

1. #### Server Operation:

Basically, it starts a server and accepts connections from clients. Upon accepting a client connection, it dispatches a thread to interact with  the client.

2. #### Client Operation:

It will connect to the server then it will ask the user to enter one of the operations.

### Compiling 

Compile your C programs by running the MakeFile.

### Running 

```c
./server
```

After running the server, it will listen to the client:

```c
Server socket created successfully
Binding successfull.
Listening:
```

After running the client, it will choose from the list:

```c
Server socket created successfully.
Connected to Server.
Choose operation: 
1) Upload files
2) List files
3) Download a file
```

### Limitation

1 - There is no access control mechanism, any client connects to the server can download any of the files.

2 - No encryption for the files. 

3 - A client can only do 1 operation then disconnects.
