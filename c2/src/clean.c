/*
** EPITECH PROJECT, 2025
** ~/epitech/free-project/Nextrace/c2
** File description:
** clean
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "server.h"

static void suppress_actual_client(node_client_t **head,
    node_client_t *to_delete, node_client_t *previous)
{
    if (previous == NULL)
        *head = to_delete->next;
    else
        previous->next = to_delete->next;
    if (to_delete->client) {
        if (to_delete->client->socket_fd != -1)
            close(to_delete->client->socket_fd);
        free(to_delete->client);
    }
    free(to_delete);
}

void delete_client_by_port(node_client_t **head, int port, char *address)
{
    node_client_t *current = *head;
    node_client_t *previous = NULL;

    while (current != NULL) {
        if (current->client->port == port &&
            strcmp(current->client->ip_address, address) == 0) {
            suppress_actual_client(head, current, previous);
            return;
        }
        previous = current;
        current = current->next;
    }
}

void detect_not_closed(node_client_t *current)
{
    if (current->client->socket_fd != -1)
        close(current->client->socket_fd);
}

void delete_all_clients(node_client_t *head)
{
    node_client_t *current = head;
    node_client_t *next;

    while (current != NULL) {
        next = current->next;
        if (current->client) {
            detect_not_closed(current);
            free(current->client);
        }
        free(current);
        current = next;
    }
}
