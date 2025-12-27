##
## EPITECH PROJECT, 2025
## ~/epitech/free-project
## File description:
## Makefile
##

CC = epiclang

SRC-AGENT = agent/src/main.c \
	agent/src/connection.c \

SRC-ASM = agent/asm/syscalls.S

SRC-C2 = c2/src/cli.c \
		  c2/src/server.c \
		  c2/src/main.c \
		  c2/src/clean.c \
		  c2/src/seed.c

OBJC2 = $(SRC-C2:.c=.o)

OBJ = $(SRC-AGENT:.c=.o)
OBJ += $(SRC-ASM:.S=.o)

NAME-C2 = nextrace
NAME = agent-trace

CFLAGS = -Wall -Wextra -Iagent/include
CFLAGS += -Ic2/include


all: $(NAME) $(NAME-C2)

$(NAME-C2): $(OBJC2)
	$(CC) -o $(NAME-C2) $(OBJC2) $(CFLAGS)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ) $(OBJC2)

fclean: clean
	rm -f $(NAME) $(NAME-C2)

re: fclean all