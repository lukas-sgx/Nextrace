/*
** EPITECH PROJECT, 2025
** ~/epitech/free-project/Nextrace/c2
** File description:
** server
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include "cli.h"
#include "server.h"

int create_socket(void)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    return sockfd;
}

static void set_timeout(int socket_fd, int timeout_sec)
{
    struct timeval tv;

    tv.tv_sec = timeout_sec;
    tv.tv_usec = 100000;
    setsockopt(socket_fd, SOL_SOCKET, SO_RCVTIMEO,
        (const char *)&tv, sizeof(tv));
}

static void launch_server(int server_fd, struct sockaddr_in *address, int port)
{
    address->sin_family = AF_INET;
    address->sin_addr.s_addr = INADDR_ANY;
    address->sin_port = htons(port);
    bind(server_fd, (struct sockaddr *)address, sizeof(*address));
    if (listen(server_fd, 10) == -1)
        exit(1);
    set_timeout(server_fd, 0);
}

static int close_client(client_args_t *client_args, int ret)
{
    if (ret == 0) {
        printf("\n" BLUE "[-] " RESET "Session ended " RESET "\n");
        write(1, "nex> ", 5);
        delete_client_by_port(client_args->clients,
            client_args->port, client_args->address);
        return 0;
    }
    if (ret < 0) {
        sleep(1);
        if (errno == EAGAIN || errno == EWOULDBLOCK)
            return 1;
        printf("\n" BLUE "[-] " RESET "Connection %s:%d lost\n",
            client_args->address, client_args->port);
        write(1, "nex> ", 5);
        return 0;
    }
    return 2;
}

void *connect_client(void *arg)
{
    client_args_t *client_args = (client_args_t *)arg;
    int new_socket = *(client_args->pclient);
    char buffer[1024];
    int ret = 0;

    printf("\n" RED "[+] " RESET "Session started " RESET "\n");
    write(1, "nex> ", 5);
    while (TRUE) {
        ret = recv(new_socket, buffer, sizeof(buffer), MSG_DONTWAIT);
        if (close_client(client_args, ret) == 0)
            break;
        sleep(1);
    }
    if (new_socket != -1)
        close(new_socket);
    free(client_args->pclient);
    free(client_args);
    return NULL;
}

static void cli_handler(int port, server_t *server)
{
    pthread_t cli_thread;

    printf(BLUE"[*] " RESET "Deploy on port %d\n\n", port);
    pthread_create(&cli_thread, NULL, (void *)cli, server);
    pthread_detach(cli_thread);
}

static void client_handler(int *client_socket,
    node_client_t **clients,
    client_args_t *args)
{
    pthread_t tid;

    args->clients = clients;
    args->pclient = malloc(sizeof(int));
    *(args->pclient) = *client_socket;
    pthread_create(&tid, NULL, (void *)connect_client, args);
    pthread_detach(tid);
}

void connection_handler(int *server_fd, struct sockaddr_in *address,
    node_client_t **clients, int *unique_id)
{
    int client = 0;
    socklen_t addrlen = sizeof(*address);
    client_t *new_client = NULL;
    client_args_t *args = NULL;

    while (*server_fd != -1) {
        addrlen = sizeof(*address);
        client = accept(*server_fd, (struct sockaddr *)address, &addrlen);
        if (client < 0)
            continue;
        seed_client(client, address, &new_client, unique_id);
        push_client(clients, new_client);
        args = malloc(sizeof(client_args_t));
        args->port = new_client->port;
        args->address = new_client->ip_address;
        args->unique_id = *unique_id;
        client_handler(&client, clients, args);
    }
}

int server(int port)
{
    int server_fd = create_socket();
    struct sockaddr_in address;
    server_t *server = malloc(sizeof(server_t));
    int unique_id = 0;

    server->server_fd = &server_fd;
    server->clients = NULL;
    launch_server(server_fd, &address, port);
    cli_handler(port, server);
    connection_handler(server->server_fd, &address, &server->clients,
        &unique_id);
    delete_all_clients(server->clients);
    if (server_fd != -1)
        close(server_fd);
    free(server);
    return 0;
}
