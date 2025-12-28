/*
** EPITECH PROJECT, 2025
** ~/epitech/free-project/Nextrace/c2
** File description:
** commands
*/

#include <stdio.h>
#include "server.h"

int display_clients(node_client_t **clients)
{
    node_client_t *current = *clients;

    printf("Active sessions\n===============\n\n");
    if (current != NULL)
        printf("ID:\tIP Address\t\n");
    else {
        printf("No active sessions\n");
        return 0;
    }
    while (current != NULL) {
        printf("%d\t%s:%d\n", current->client->id,
            current->client->ip_address, current->client->port);
        current = current->next;
    }
    return 0;
}

int help_command(void)
{
    printf("Available commands\n==================\n\n");
    printf("sessions\tList all active sessions\n");
    printf("help\t\tShow this help message\n");
    printf("exit\t\tTerminate the server\n");
    return 0;
}
