#include "client_handler.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <string>
using namespace std;

void handleClient(int client_fd, bool verbose, bool httpMode) {
    char buffer[2048];

    // Set the socket to non-blocking mode

    while (true) {  // Wait for data

        if (verbose)
            cout << "[INFO] Waiting for data..." << endl;
        memset(buffer, 0, sizeof(buffer));
        ssize_t bytes_received = recv(client_fd, buffer, sizeof(buffer) - 1, 0);

        if (bytes_received <= 0) {
            if (verbose)
                cout << "[INFO] Client disconnected.\n";
            break;
        }

        string request(buffer);
        string response;
        // HTTP mode
        if (httpMode &&
            request.find("GET ") == 0) {  // Check if it's an HTTP GET request
            size_t pos1 = request.find("GET ");    // Find the start of the path
            size_t pos2 = request.find(" HTTP/");  // Find the end of the path
            string path = (pos1 != string::npos && pos2 != string::npos)
                              ? request.substr(pos1 + 4, pos2 - (pos1 + 4))
                              : "/";
            if (verbose && path != "/favicon.ico")  // Ignore favicon requests
                cout << "[HTTP] Path: " << path << endl;

            string body =
                "You requested: " + path + "\n";  // Create a response body

            response = "HTTP/1.1 200 OK\r\n";
            response += "Content-Type: text/plain\r\n";
            response += "Content-Length: " + to_string(body.length()) + "\r\n";
            response += "Connection: keep-alive\r\n\r\n";
            response += body;
        } else {
            if (verbose)
                cout << "[ECHO] Received: " << request;
            response = request;
        }

        send(client_fd, response.c_str(), response.length(),
             0);  // Send the response
    }

    close(client_fd);  // Close the client socket
}
