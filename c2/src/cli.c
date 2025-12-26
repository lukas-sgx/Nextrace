/*
** EPITECH PROJECT, 2025
** ~/epitech/free-project/Nextrace/c2
** File description:
** cli
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int handle_command(char *input)
{
    if (strncmp(input, "exit", 4) == 0)
        return 1;
    return 0;
}

int cli(void *arg)
{
    int *server_fd = (int *)arg;
    char *input = NULL;
    size_t len = 0;

    while (1) {
        printf("nex > ");
        getline(&input, &len, stdin);
        if (handle_command(input) != 0)
            break;
    }
    close(*server_fd);
    *server_fd = -1;
    free(input);
    return 0;
}