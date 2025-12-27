/*
** EPITECH PROJECT, 2025
** ~/epitech/free-project/Nextrace/c2
** File description:
** seed
*/

#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include "server.h"

void push_client(node_client_t **head, client_t *new_client)
{
    node_client_t *new_node = malloc(sizeof(node_client_t));

    new_node->client = new_client;
    new_node->next = *head;
    *head = new_node;
}

void seed_client(int client, struct sockaddr_in *address,
    client_t **new_client)
{
    *new_client = malloc(sizeof(client_t));
    (*new_client)->socket_fd = client;
    (*new_client)->ip_address = strdup(inet_ntoa(address->sin_addr));
    (*new_client)->port = ntohs(address->sin_port);
}
