#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "server.h"

// Function to print usage information
void printUsage(const char* program) {
    printf("Usage: %s [-p port] [-v] [--http]\n", program);
}

// Function to parse command-line arguments and start the server
int main(int argc, char* argv[]) {
    int port     = 8080;  // Default port
    int verbose  = 0;     // Verbose mode
    int httpMode = 0;     // HTTP mode

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) {
            port = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-v") == 0) {
            verbose = 1;
        } else if (strcmp(argv[i], "--http") == 0) {
            httpMode = 1;
        } else {
            printUsage(argv[0]);
            return 1;
        }
    }

    // Call the startServer
    startServer(port, verbose, httpMode);
    return 0;
}
