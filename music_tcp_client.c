/**
Author: Sasi Kumar Reddy
Client program: mp3 music streaming via TCP socket
Dependency: mpg123 [sudo apt install mpg123]
**/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8800
#define BUFFER_SIZE 1024

void send_request(int server_socket, const char *request) {
    send(server_socket, request, strlen(request), 0);
}

void play_streamed_mp3(int server_socket) {
    FILE *mpg123_pipe = popen("mpg123 -", "w");
    if (!mpg123_pipe) {
        perror("Error opening mpg123 pipe");
        exit(EXIT_FAILURE);
    }

    char buffer[4096];
    ssize_t bytes_received;

    while ((bytes_received = recv(server_socket, buffer, sizeof(buffer), 0)) > 0) {
        if (fwrite(buffer, 1, bytes_received, mpg123_pipe) != bytes_received) {
            perror("Error writing to mpg123 pipe");
            exit(EXIT_FAILURE);
        }
    }

    if (bytes_received == -1) {
        perror("Error receiving data");
        exit(EXIT_FAILURE);
    }

    // Close the write end of the pipe to signal end of input
    fclose(mpg123_pipe);
    pclose(mpg123_pipe);
}


int main() {
    int client_socket;
    struct sockaddr_in server_addr;

    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Initialize server address structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("192.168.0.105"); // Server IP address
    server_addr.sin_port = htons(PORT);

    // Connect to the server
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error connecting to server");
        exit(EXIT_FAILURE);
    }

    // Read user input
    char command[BUFFER_SIZE] ;  
    printf("Enter song number (1-9): ");
    fgets(command, sizeof(command), stdin);
    printf("\n\n**** Kill the process and re-run the program to listen to a different song ****\n\n");
    send_request(client_socket, command);
    play_streamed_mp3(client_socket);
        
    // Close the client socket
    close(client_socket);

    exit(0);
}
