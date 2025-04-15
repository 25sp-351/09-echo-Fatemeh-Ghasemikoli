#include <cstring>
#include <iostream>

#include "server.h"
using namespace std;

// Function to print usage information
void printUsage(const char* program) {
    cout << "Usage: " << program << " [-p port] [-v] [--http]" << endl;
}
// Function to parse command-line arguments and start the server
int main(int argc, char* argv[]) {
    int port      = 8080;   // Default port
    bool verbose  = false;  // Verbose mode
    bool httpMode = false;  // HTTP mode

    for (int i = 1; i < argc; i++) {  // Parse command-line arguments
        if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) {
            port = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-v") == 0) {
            verbose = true;
        } else if (strcmp(argv[i], "--http") == 0) {
            httpMode = true;
        } else {
            printUsage(argv[0]);
            return 1;
        }
    }
    // Start the server with the specified options
    startServer(port, verbose, httpMode);
    return 0;
}
