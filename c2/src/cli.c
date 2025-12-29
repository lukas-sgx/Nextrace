/*
** EPITECH PROJECT, 2025
** ~/epitech/free-project/Nextrace/c2
** File description:
** cli
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include "server.h"

int handle_command(char *input, node_client_t **clients)
{
    if (strncmp(input, "exit", 4) == 0)
        return 1;
    if (strncmp(input, "help", 4) == 0) {
        help_command();
        return 0;
    }
    if (strncmp(input, "\n", 1) == 0)
        return 0;
    if (strncmp(input, "sessions", 8) == 0) {
        sessions_handler(input, clients);
        return 0;
    }
    printf("Unknown command: %s", input);
    return 0;
}

int cli(void *arg)
{
    server_t *server = (server_t *)arg;
    char *input = NULL;
    size_t len = 0;

    while (TRUE) {
        printf("nex> ");
        fflush(stdout);
        if (getline(&input, &len, stdin) == -1)
            break;
        if (handle_command(input, &server->clients) != 0)
            break;
    }
    if (*server->server_fd != -1) {
        shutdown(*server->server_fd, SHUT_RDWR);
        close(*server->server_fd);
        *server->server_fd = -1;
    }
    free(input);
    return 0;
}
