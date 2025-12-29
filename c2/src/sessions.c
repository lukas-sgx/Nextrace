/*
** EPITECH PROJECT, 2025
** ~/epitech/free-project/Nextrace/c2
** File description:
** sessions
*/

#include <string.h>
#include <stdlib.h>
#include "server.h"

int sessions_handler(char *input, node_client_t **clients)
{
    int id = 0;

    if (strncmp(input, "sessions -k ", 11) == 0) {
        id = atoi(input + 11);
        kill_session(id, clients);
        return 0;
    }
    if (strncmp(input, "sessions", 8) == 0) {
        display_clients(clients);
        return 0;
    }
    return 0;
}
