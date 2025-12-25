##
## EPITECH PROJECT, 2025
## ~/epitech/free-project
## File description:
## Makefile
##

CC = clang

SRC-AGENT = agent/src/main.c 

SRC-ASM = agent/asm/syscalls.S

OBJ = $(SRC-AGENT:.c=.o)
OBJ += $(SRC-ASM:.S=.o)

NAME = agent-trace

CFLAGS = -Wall -Wextra -Iagent/include


all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all