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
#include "cli.h"

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
    listen(server_fd, 3);
    set_timeout(server_fd, 0);
}

void *connect_client(void *arg)
{
    int new_socket = *(int *)arg;

    printf("[NEXTRACE] New connection accepted (socket fd: %d)\n", new_socket);
    close(new_socket);
    write(1, "nex > ", 6);
    printf("[NEXTRACE] Connection closed (socket fd: %d)\n", new_socket);
    write(1, "nex > ", 6);
    return NULL;
}

void cli_handler(int *server_fd, int port)
{
    pthread_t cli_thread;

    printf("[NEXTRACE] Service started on port %d\n", port);
    pthread_create(&cli_thread, NULL, (void *)cli, (void *)server_fd);
    pthread_detach(cli_thread);
}

void connection_handler(int *server_fd, struct sockaddr_in *address)
{
    pthread_t tid;
    int client = 0;
    socklen_t addrlen = sizeof(*address);

    while (*server_fd != -1) {
        addrlen = sizeof(*address);
        client = accept(*server_fd, (struct sockaddr *)address, &addrlen);
        if (client < 0)
            continue;
        pthread_create(&tid, NULL, (void *)connect_client, &client);
        pthread_detach(tid);
    }
}

int server(int port)
{
    int server_fd = create_socket();
    struct sockaddr_in address;

    launch_server(server_fd, &address, port);
    cli_handler(&server_fd, port);
    connection_handler(&server_fd, &address);
    close(server_fd);
    return 0;
}
