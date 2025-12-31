/*
** EPITECH PROJECT, 2025
** ~/epitech/free-project/Nextrace/agent
** File description:
** connection
*/

#ifndef CONNECTION_H_
    #define CONNECTION_H_

    #define RED "\033[31m"
    #define BLUE "\033[34m"
    #define RESET "\033[0m"

void establish_connection(char *ip_address, int port);

extern int exit_force(int error_code);

#endif /* CONNECTION_H_ */