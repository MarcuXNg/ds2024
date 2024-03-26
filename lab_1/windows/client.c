#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h> // Include the Winsock library
#include <ws2tcpip.h>

#define PORT 8080
#define SIZE 1024

int main() {
    char *ip = "127.0.0.1";
    char buffer[SIZE];
    WSADATA wsa;
    SOCKET client_socket;
    struct sockaddr_in server_ip;
    FILE *file;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup failed\n");
        return 1;
    }

    // Create a socket
    if ((client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
        printf("Failed to create socket\n");
        return 1;
    }

    // Fill in server details
    server_ip.sin_family = AF_INET;
    server_ip.sin_port = htons(PORT);
    inet_pton(AF_INET, ip, &server_ip.sin_addr);

    // Connect to server
    if (connect(client_socket, (struct sockaddr *)&server_ip, sizeof(server_ip)) == SOCKET_ERROR) {
        printf("Failed to connect to server\n");
        closesocket(client_socket);
        WSACleanup();
        return 1;
    }

    printf("Connected to server\n");

    // Open file
    file = fopen("C:\\Users\\Administrator\\Downloads\\Writeup\\ds2024\\test.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        closesocket(client_socket);
        WSACleanup();
        return 1;
    }

    // Read file and send data
    ssize_t bytes_read;
    while ((bytes_read = fread(buffer, 1, SIZE, file)) > 0) {
        ssize_t bytes_sent = send(client_socket, buffer, bytes_read, 0);
        if (bytes_sent == SOCKET_ERROR) {
            printf("Error sending data to server\n");
            fclose(file);
            closesocket(client_socket);
            WSACleanup();
            return 1;
        }
    }
    
    printf("Data sent successfully to server\n");

    // Close file and socket
    fclose(file);
    closesocket(client_socket);
    WSACleanup();

    return 0;
}
