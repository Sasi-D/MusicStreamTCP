# Concurrent Music Streaming Over TCP
MusicStreamTCP is a project that provides both a server and client application for streaming music over TCP. It enables efficient and reliable transmission of audio data between a server and clients.

## Client application
Client application won't take any command-line arguments. Multiple instances of client's can be instantiated from same end-host. To run Client use the following commands : 
```sh
gcc -o client music_tcp_client.c
./client
```


## Server application
The server application is multi-threaded, enabling it to stream songs concurrently to multiple clients. It requires three command line arguments: the port number (P) on which it will listen, the root directory (DIR) of the MP3 song folder, and the maximum number of simultaneous streams (N) it can support respectively. To run Server use the following commands:
```sh
gcc -o server music_tcp_server.c
./server <port> <DIR> <N>
```

Client uses **mpg123** dependency to play songs. You can install this dependency in linux by using one of the following command depending on linux distro being used:
```sh
sudo apt install mpg123 
sudo dnf install mpg123
flatpak install mpg123
sudo pacman install mpg123
```