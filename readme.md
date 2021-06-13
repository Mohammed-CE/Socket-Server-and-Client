# Storage Server Project 

In this project, we will test the capabilities of different IPC mechanisms and we use one of them. The goal of this project is to build a complete and secure system for serving and uploading files listed in single directory.

**Prepared by:** Saad Alsubaie, Mohammed Almansour and Yasir Alharbi.

### System Components

The system of our project consist of following:

- Server process.
- Client process.
- Inter-Process-Communication ( Connection Oriented Protocol TCP ).

### Socket programming 

Socket programming is a way of connecting two nodes on a network to  communicate with each other. One socket(node) listens on a particular  port at an IP, while other socket reaches out to the other to form a  connection. Server forms the listener socket while client reaches out to the server. See below figure which describe the connection process between server and client.![https://user-images.githubusercontent.com/19291492/44955905-363dae80-aef6-11e8-9719-ac759adbdfaa.png](https://user-images.githubusercontent.com/19291492/44955905-363dae80-aef6-11e8-9719-ac759adbdfaa.png)

##### socket type:

In this project we the SOCK_STREAM: TCP(reliable, connection oriented) type.

#### Client Process & Server Process:

1. ##### server :

Takes request from the clients, perform required processing, and send it to the client.

- Create a socket with the `socket()` system call.

- Bind the socket to an address (IP + port) using the `bind()` system call.

- Listen for connections with the `listen()` system call.

- Accept a connection with the `accept()` system call then create a thread for the client. This call typically blocks the connection until a client connects with the server.

- Send and receive data using the `read()` and `write()` system calls.


2. ##### client :

Typically request to server for information.

- Create a socket with the `socket()` system call.

- Connect socket to the address of the server using the `connect()` system call.

- Send and receive data. There are a number of ways to do this, but the simplest way is to use the `read()` and `write()` system calls.

  

### Operation Types 

1. #### Server Operation:

   The `server1.c` is the code for the server. Basically, it starts a server and accepts connections from clients. Upon accepting a client connection, it dispatches a thread to interact with  the client.

2. #### Client Operation:

the `client1.c` is the code for the client. firstly it will  connect to the server in the local host then will ask the user to enter one of the operations.

### Compiling 

Compile your C programs by running Make file which include:

```c
gcc server1.c -o server
gcc client1.c -o client 
```

### Running 

Run the server program on the server by running:

```c
./server
```

After running the server will listen to the client:

```c
Server socket created successfully
Binding successfull.
Listening:
```

Run the client program on the server by running:

```c
./client 
```

The client which choice from list consist three process:

```c
Server socket created successfully.
Connected to Server.
Choose operation: 
1) Upload files
2) List files
3) Download a file
```

The server will implement the operation that the client was selected.

### Limitation

1 - There isn't access control mechanism, any client connects to the server can download any of the files.

2 - No encryption for the files. 

3 - A client can only do 1 operation then disconnects.
