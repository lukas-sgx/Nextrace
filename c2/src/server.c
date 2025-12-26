/*
** EPITECH PROJECT, 2025
** ~/epitech/free-project/Nextrace/c2
** File description:
** server
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>

int create_socket(void)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    return sockfd;
}

void launch_server(int server_fd, struct sockaddr_in *address, int port)
{
    address->sin_family = AF_INET;
    address->sin_addr.s_addr = INADDR_ANY;
    address->sin_port = htons(port);
    bind(server_fd, (struct sockaddr *)address, sizeof(*address));
    listen(server_fd, 3);
}

void connect_client(int server_fd)
{
    int new_socket = accept(server_fd, NULL, NULL);
    
    printf("[NEXTRACE] New connection accepted (socket fd: %d)\n", new_socket);
    close(new_socket);
    printf("[NEXTRACE] Connection closed (socket fd: %d)\n", new_socket);
}

int server(int port)
{
    int server_fd = create_socket();
    struct sockaddr_in address;

    launch_server(server_fd, &address, port);
    printf("[NEXTRACE] Service started on port %d\n", port);
    while (server_fd != -1) {
        connect_client(server_fd);
    }
    
    return 0;
}