#include "server.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <thread>

#include "client_handler.h"
using namespace std;

// Function to start the server
// and listen for incoming connections
void startServer(int port, bool verbose, bool httpMode) {
    int server_fd;
    struct sockaddr_in address;
    int opt     = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {  // Create socket
        perror("socket failed");
        return;
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
        return;
    }

    address.sin_family      = AF_INET;      // IPv4
    address.sin_addr.s_addr = INADDR_ANY;   // Any address
    address.sin_port        = htons(port);  // Port number
    // Bind the socket to the specified port
    if (::bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        return;
    }
    // Listen for incoming connections
    if (listen(server_fd, 10) < 0) {
        perror("listen");
        close(server_fd);
        return;
    }

    cout << (httpMode ? "HTTP" : "Echo") << " Server listening on port " << port
         << "..." << endl;

    while (true) {  // Accept incoming connections
        int client_fd =
            accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
        if (client_fd < 0) {
            perror("accept");
            continue;
        }

        thread(handleClient, client_fd, verbose, httpMode)
            .detach();  // Handle client in a separate thread
    }

    close(server_fd);
}
