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

int check_read(char *buffer)
{
	if (strlen(buffer) >= 4 && buffer[0] >= '0' && buffer[0] <= '9' &&
		buffer[1] >= '0' && buffer[1] <= '9' &&
		buffer[2] >= '0' && buffer[2] <= '9' &&
		buffer[3] == ' ')
		return (1);
	return (0);
}

int create_socket(t_serveur *serveur, char *proto_name)
{
	struct protoent *pe;

	pe = getprotobyname(proto_name);
	if (!pe)
		return (fprintf(stderr, "Getprotobyname failed\n"), 1);
	serveur->socket_fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	if (serveur->socket_fd == -1)
		return (fprintf(stderr, "Socket failed\n"), 1);
	serveur->s_in.sin_family = AF_INET;
	serveur->s_in.sin_port = htons(serveur->port);
	serveur->s_in.sin_addr.s_addr = inet_addr(serveur->ip);
	if (connect(serveur->socket_fd,(struct sockaddr *)
		&serveur->s_in, sizeof(serveur->s_in)) == -1) {
		if (close(serveur->socket_fd) == -1)
			return (fprintf(stderr, "Close failed\n"), 1);
		return (1);
	}
	return (0);
}
