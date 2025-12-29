/*
** EPITECH PROJECT, 2025
** ~/epitech/free-project/Nextrace/c2
** File description:
** commands
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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

int found_kill_client(int id, node_client_t **clients,
    node_client_t *current, node_client_t *previous)
{
    if (current->client->id == id) {
        if (previous == NULL)
            *clients = current->next;
        else
            previous->next = current->next;
        if (current->client->socket_fd != -1) {
            shutdown(current->client->socket_fd, SHUT_RDWR);
            close(current->client->socket_fd);
        }
        free(current->client);
        free(current);
        printf(BLUE "[-] " RESET "Session %d terminated successfully\n", id);
        return 0;
    }
    previous = current;
    current = current->next;
    return 0;
}

int kill_session(int id, node_client_t **clients)
{
    node_client_t *current = *clients;
    node_client_t *previous = NULL;

    while (current != NULL)
        if (found_kill_client(id, clients, current, previous) == 0)
            return 0;
    printf("Session with ID %d not found\n", id);
    return -1;
}

int help_command(void)
{
    printf("Available commands\n==================\n\n");
    printf("sessions\tList all active sessions\n");
    printf("help\t\tShow this help message\n");
    printf("exit\t\tTerminate the server\n");
    return 0;
}
