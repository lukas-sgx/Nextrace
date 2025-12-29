/*
** EPITECH PROJECT, 2025
** ~/epitech/free-project/Nextrace/c2
** File description:
** server
*/

#ifndef SERVER_H_
    #define SERVER_H_

    #include <netinet/in.h>

    #define TRUE 1
    #define FALSE 0
    #define RED "\033[31m"
    #define GREEN "\033[32m"
    #define YELLOW "\033[33m"
    #define BLUE "\033[34m"
    #define MAGENTA "\033[35m"
    #define CYAN "\033[36m"
    #define RESET "\033[0m"

typedef struct client_s
{
    int socket_fd;
    char *ip_address;
    int port;
    int id;
} client_t;

typedef struct node_client_s
{
    client_t *client;
    struct node_client_s *next;
} node_client_t;

typedef struct server_s
{
    int *server_fd;
    node_client_t *clients;
} server_t;

typedef struct client_args_s
{
    node_client_t **clients;
    int *pclient;
    int port;
    char *address;
    int unique_id;
} client_args_t;

int server(int port);
void delete_all_clients(node_client_t *head);
void delete_client_by_port(node_client_t **head, int port, char *address);
void seed_client(int client, struct sockaddr_in *address,
    client_t **new_client, int *unique_id);
void push_client(node_client_t **head, client_t *new_client);
int help_command(void);
int display_clients(node_client_t **clients);
int sessions_handler(char *input, node_client_t **clients);
int kill_session(int id, node_client_t **clients);
#endif /* SERVER_H_ */
