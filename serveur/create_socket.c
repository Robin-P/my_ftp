/*
** EPITECH PROJECT, 2018
** mdr
** File description:
** mdr
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include "serveur.h"

int bind_listen(t_serveur *serveur)
{
	if ((bind(serveur->socket_fd, (const struct sockaddr *)&serveur->s_in,
		sizeof(serveur->s_in))) == -1) {
		if (close(serveur->socket_fd) == -1)
			return (fprintf(stderr, "Close failed\n"), 0);
		return (fprintf(stderr, "Bind failed\n"), 0);
	}
	if (listen(serveur->socket_fd, 42) == -1) {
		if (close(serveur->socket_fd) == -1)
			return (fprintf(stderr, "Close failed\n"), 0);
		return (fprintf(stderr, "Listen failed\n") , 0);
	}
	return (1);
}

int create_socket(t_serveur *serveur, char *proto_name)
{
	struct protoent *pe;

	pe = getprotobyname(proto_name);
	if (!pe)
		return (fprintf(stderr, "Getprotobyname failed\n"), 0);
	serveur->socket_fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	if (serveur->socket_fd == -1)
		return (fprintf(stderr, "Socket failed\n"), 0);
	serveur->s_in.sin_family = AF_INET;
	serveur->s_in.sin_port = htons(serveur->port);
	serveur->s_in.sin_addr.s_addr = INADDR_ANY;
	if (bind_listen(serveur) == 0)
		return (0);
	return (1);
}
