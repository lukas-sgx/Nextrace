/*
** EPITECH PROJECT, 2025
** ~/epitech/free-project/Nextrace/agent
** File description:
** connection
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <signal.h>
#include "connection.h"

// int try_reconnect(int socket_fd)
// {
//     int ret = 0;
//     struct sockaddr_in serv_addr;

//     serv_addr.sin_family = AF_INET;
//     serv_addr.sin_port = htons(8080);
//     inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

//     while (1) {
//         ret = connect(socket_fd, (struct sockaddr *)&serv_addr,
//             sizeof(serv_addr));
//         if (ret == 0) {
//             write(1, "[NEXTRACE] Reconnected to server successfully\n", 45);
//             return 0;
//         }
//         sleep(5);
//     }
//     return -1;
// }

void *signal_waiter(void *arg)
{
    int socket_fd = *(int *)arg;
    sigset_t set;
    int sig;

    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGTERM);
    sigwait(&set, &sig);
    write(1, "\n[NEXTRACE] Disconnecting from server...\n", 41);
    shutdown(socket_fd, SHUT_RDWR);
    close(socket_fd);
    exit_force(0);
    return NULL;
}

void *recv_handler(void *arg)
{
    char buffer[1024];
    int ret = 0;
    int *socket_fd = (int *)arg;

    while (1) {
        ret = recv(*socket_fd, buffer, sizeof(buffer), 0);
        if (ret <= 0) {
            write(1, "\n[NEXTRACE] Disconnected from server\n", 36);
            shutdown(*socket_fd, SHUT_RDWR);
            close(*socket_fd);
            exit_force(0);
        }
    }
    return NULL;
}

void *send_handler(void *arg)
{
    int *socket_fd = (int *)arg;

    while (1) {
        if (send(*socket_fd, "KEEPALIVE", 9, MSG_NOSIGNAL) < 0)
            break;
        sleep(5);
    }
    return NULL;
}

int keep_alive(int socket_fd)
{
    pthread_t recv_thread;
    pthread_t send_thread;

    if (pthread_create(&recv_thread, NULL, recv_handler, &socket_fd) != 0)
        return -1;
    if (pthread_create(&send_thread, NULL, send_handler, &socket_fd) != 0)
        return -1;
    pthread_join(recv_thread, NULL);
    pthread_cancel(send_thread);
    pthread_join(send_thread, NULL);
    return 0;
}

static void set_signal_mask(void)
{
    sigset_t set;

    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGTERM);
    pthread_sigmask(SIG_BLOCK, &set, NULL);
}

void establish_connection(char *ip_address, int port)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in serv_addr;
    pthread_t sig_thread;

    set_signal_mask();
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip_address, &serv_addr.sin_addr);
    if (sockfd == -1)
        return;
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
        write(1, "[NEXTRACE] Connection to server failed\n", 39);
    else {
        write(1, "[NEXTRACE] Connected to server successfully\n", 44);
        if (pthread_create(&sig_thread, NULL, signal_waiter, &sockfd) == 0) {
            pthread_detach(sig_thread);
        }
        keep_alive(sockfd);
    }
    close(sockfd);
}
