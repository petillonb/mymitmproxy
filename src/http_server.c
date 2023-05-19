#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8085
#define BUFFER_SIZE 1024

void handle_request(int client_socket)
{
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    // Read the request from the client
    bytes_read = read(client_socket, buffer, BUFFER_SIZE - 1);
    if (bytes_read < 0)
    {
        perror("Error reading from socket");
        return;
    }

    buffer[bytes_read] = '\0';

    // Print the request
    printf("Received request:\n%s\n", buffer);

    // Send the HTTP response
    const char *response = "HTTP/1.1 200 OK\r\n"
                           "Content-Length: 18\r\n"
                           "Content-Type: text/html\r\n"
                           "\r\n"
                           "<h1>Hello, World!</h1>";
    ssize_t bytes_sent = write(client_socket, response, strlen(response));
    if (bytes_sent < 0)
    {
        perror("Error writing to socket");
        return;
    }
}

int start_HTTP_server()
{
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_length;

    // Create the server socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0)
    {
        perror("Error creating socket");
        return 1;
    }

    // Set up the server address
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    // Bind the server socket to the specified address and port
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        perror("Error binding socket");
        return 1;
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) < 0)
    {
        perror("Error listening");
        return 1;
    }

    printf("Server is running on port %d...\n", PORT);

    while (1)
    {
        // Accept a client connection
        client_address_length = sizeof(client_address);
        client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_length);
        if (client_socket < 0)
        {
            perror("Error accepting connection");
            return 1;
        }

        // Handle the client request
        handle_request(client_socket);

        // Close the client socket
        close(client_socket);
    }

    // Close the server socket
    close(server_socket);

    return 0;
}
