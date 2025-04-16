#include "client_handler.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void handleClient(int client_fd, int verbose,
                  int httpMode) {  // Function to handle client connections
    char buffer[2048];             // I need Buffer to store incoming data

    while (1) {
        if (verbose)
            printf(" Waiting for data...\n");

        memset(buffer, 0, sizeof(buffer));
        ssize_t bytes_received = recv(client_fd, buffer, sizeof(buffer) - 1, 0);

        if (bytes_received <= 0) {
            if (verbose)
                printf(" Client disconnected.\n");
            break;
        }

        // HTTP mode
        if (httpMode && strstr(buffer, "GET ") == buffer) {
            char* start     = buffer + 4;
            char* end       = strstr(start, " HTTP/");
            char path[1024] = "/";

            if (start && end && (end - start < sizeof(path))) {
                strncpy(path, start, end - start);
                path[end - start] = '\0';
            }

            if (verbose && strcmp(path, "/favicon.ico") != 0)
                printf("[HTTP] Path: %s\n", path);

            char body[2048];
            snprintf(body, sizeof(body), "You requested: %s\n", path);

            char response[4096];
            snprintf(response, sizeof(response),
                     "HTTP/1.1 200 OK\r\n"
                     "Content-Type: text/plain\r\n"
                     "Content-Length: %lu\r\n"
                     "Connection: keep-alive\r\n\r\n"
                     "%s",
                     strlen(body), body);

            send(client_fd, response, strlen(response), 0);
        } else {
            if (verbose)
                printf("[ECHO] Received: %s", buffer);

            send(client_fd, buffer, bytes_received, 0);
        }
    }

    close(client_fd);
}
