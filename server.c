#include "server.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "client_handler.h"

struct ThreadArgs {
    int client_fd;
    int verbose;
    int httpMode;
};

void* clientThread(void* arg) {
    struct ThreadArgs* args = (struct ThreadArgs*)arg;
    handleClient(args->client_fd, args->verbose, args->httpMode);
    free(arg);  // Free the memory allocated for arguments
    return NULL;
}

void startServer(int port, int verbose, int httpMode) {
    int server_fd;
    struct sockaddr_in address;
    int opt     = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        return;
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
        return;
    }

    address.sin_family      = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port        = htons(port);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        return;
    }

    if (listen(server_fd, 10) < 0) {
        perror("listen");
        close(server_fd);
        return;
    }

    printf("%s Server listening on port %d...\n", httpMode ? "HTTP" : "Echo",
           port);

    while (1) {
        int client_fd =
            accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
        if (client_fd < 0) {
            perror("accept");
            continue;
        }

        struct ThreadArgs* args = malloc(sizeof(struct ThreadArgs));
        if (!args) {
            perror("malloc failed");
            close(client_fd);
            continue;
        }

        args->client_fd = client_fd;
        args->verbose   = verbose;
        args->httpMode  = httpMode;

        pthread_t tid;
        if (pthread_create(&tid, NULL, clientThread, args) != 0) {
            perror("pthread_create failed");
            close(client_fd);
            free(args);
        } else {
            pthread_detach(tid);
        }
    }

    close(server_fd);
}
