##
## EPITECH PROJECT, 2018
## mdr
## File description:
## mdr
##

SERVEUR	=	server

CLIENT	=	client

CC	=	gcc

RM	=	rm -f

SRCS_SERVEUR	=	./serveur/serveur.c \
			./serveur/new_client.c \
			./serveur/authentification.c \
			./serveur/cmds/authentificated.c \
			./serveur/cmds/basic_cmds.c \
			./serveur/cmds/changedir_cmds.c \
			./serveur/cmds/account_cmds.c \
			./serveur/cmds/pasv_port_cmds.c \
			./serveur/create_socket.c \
			./serveur/cmds/stor.c

SRCS_CLIENT	=	./src_client/client.c \
			./src_client/create_socket.c \
			./src_client/get_pasv.c \
			./src_client/get_cmds.c \
			./src_client/loop.c

OBJS_SERVEUR	=	$(SRCS_SERVEUR:.c=.o)

OBJS_CLIENT	=	$(SRCS_CLIENT:.c=.o)

CFLAGS	=	-I include

CFLAGS	+=	-W -Wall -Wextra

LDFLAGS =

.c.o:
		@$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@ && \
		printf "[\033[1;32mcompiled\033[0m] % 29s\n" $< | tr ' ' '.' || \
		printf "[\033[1;31mfailed\033[0m] % 31s\n" $< | tr ' ' '.'

all: 		$(SERVEUR)

$(SERVEUR):	$(OBJS_SERVEUR) $(OBJS_CLIENT)
		@$(CC) $(OBJS_SERVEUR) -o $(SERVEUR) $(LDFLAGS) && \
		(printf "[\033[1;36mbuilt\033[0m] % 32s\n" $(SERVEUR) | tr ' ' '.' || \
		printf "[\033[1;31mfailed\033[0m] % 31s\n" $(SERVEUR) | tr ' ' '.') && \
		$(CC) $(OBJS_CLIENT) -o $(CLIENT) $(LDFLAGS) && \
		printf "[\033[1;36mbuilt\033[0m] % 32s\n" $(CLIENT) | tr ' ' '.' || \
		printf "[\033[1;31mfailed\033[0m] % 31s\n" $(CLIENT) | tr ' ' '.'


clean:
		@$(RM) $(OBJS_CLIENT) && \
		(printf "[\033[1;31mdeleted\033[0m] % 30s\n" $(OBJS_CLIENT) | tr ' ' '.' || \
		printf "[\033[1;31mdeleted\033[0m] % 30s\n" $(OBJS_CLIENT) | tr ' ' '.') && \
		$(RM) $(OBJS_SERVEUR) && \
		(printf "[\033[1;31mdeleted\033[0m] % 30s\n" $(OBJS_SERVEUR) | tr ' ' '.' || \
		printf "[\033[1;31mdeleted\033[0m] % 30s\n" $(OBJS_SERVEUR) | tr ' ' '.')

fclean: 	clean
		@$(RM) $(SERVEUR) && \
		(printf "[\033[1;31mdeleted\033[0m] % 30s\n" $(SERVEUR) | tr ' ' '.' || \
		printf "[\033[1;31mdeleted\033[0m] % 30s\n" $(SERVEUR) | tr ' ' '.') && \
		$(RM) $(CLIENT) && \
		(printf "[\033[1;31mdeleted\033[0m] % 30s\n" $(CLIENT) | tr ' ' '.' || \
		printf "[\033[1;31mdeleted\033[0m] % 30s\n" $(CLIENT) | tr ' ' '.')

re:		fclean all

.PHONY: 	all clean fclean re


.PHONY: 	all clean fclean re
