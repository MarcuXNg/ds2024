#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h> // Include the Winsock library
#include <ws2tcpip.h>
#include <unistd.h>
#include <fcntl.h>

#define PORT 8080
#define SIZE 1024 * 10

int main() {
    char *ip = "127.0.0.1";
    char buffer[SIZE];
    WSADATA wsa;
    SOCKET server_socket, new_socket;
    struct sockaddr_in server_ip, client_ip;
    int addr_len = sizeof(client_ip);

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup failed\n");
        return 1;
    }

    // Create a socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
        printf("Failed to create socket\n");
        return 1;
    }

    // Fill in server details
    server_ip.sin_family = AF_INET;
    server_ip.sin_port = htons(PORT);
    inet_pton(AF_INET, ip, &server_ip.sin_addr);

    // Bind the socket
    if (bind(server_socket, (struct sockaddr *)&server_ip, sizeof(server_ip)) == SOCKET_ERROR) {
        printf("Bind failed\n");
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    printf("Bind successful\n");

    // Listen for incoming connections
    if (listen(server_socket, 10) == SOCKET_ERROR) {
        printf("Listen failed\n");
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    printf("Listening for connections...\n");

    // Accept incoming connection
    if ((new_socket = accept(server_socket, (struct sockaddr *)&client_ip, &addr_len)) == INVALID_SOCKET) {
        printf("Accept failed\n");
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    printf("Connection accepted\n");

    // Open or create file
    int file_fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (file_fd == -1) {
        printf("Error opening or creating file\n");
        closesocket(new_socket);
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    // Receive data and write to file
    ssize_t bytes_received;
    while ((bytes_received = recv(new_socket, buffer, SIZE, 0)) > 0) {
        ssize_t bytes_written = write(file_fd, buffer, bytes_received);
        if (bytes_written != bytes_received) {
            printf("Error writing to file\n");
            close(file_fd);
            closesocket(new_socket);
            closesocket(server_socket);
            WSACleanup();
            return 1;
        }
    }

    if (bytes_received == -1) {
        printf("Error receiving data from client\n");
        close(file_fd);
        closesocket(new_socket);
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    printf("Data received and written to 'test.txt' successfully\n");

    // Close file and sockets
    close(file_fd);
    closesocket(new_socket);
    closesocket(server_socket);
    WSACleanup();

    return 0;
}
