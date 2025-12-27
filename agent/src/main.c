/*
** EPITECH PROJECT, 2025
** ~/epitech/free-project/Nextrace/agent
** File description:
** main
*/

#include "syscalls.h"
#include "connection.h"

int main(void)
{
    establish_connection("127.0.0.1", 8080);
    return 0;
}
