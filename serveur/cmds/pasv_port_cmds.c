/*
** EPITECH PROJECT, 2018
** mdr
** File description:
** mdr
*/

#include "maccro.h"
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include "serveur.h"

char *get_ip(int client_fd, t_serveur *serveur)
{
	char *ip = NULL;
	int serveur_size = sizeof(serveur);
	struct sockaddr_in serv;

	if (getsockname(client_fd, &serv, (socklen_t *)&serveur_size) == -1) {
		write(client_fd, "999 PASV Failed.\n",
			strlen("999 PASV Failed.\n"));
		return (fprintf(stderr, "Getsockname failed"), NULL);
	}
	ip = inet_ntoa(serv.sin_addr);
	for (size_t i = 0; i < strlen(ip); ++i)
		if (ip[i] == '.')
			ip[i] = ',';
	return (ip);
}

int get_port(t_session *s, int *port1, int *port2)
{
	while (1) {
		*port1 = rand() % 256;
		*port2 = rand() % 256;
		s->serveur.port = *port1 * 256 + *port2;
		if (create_socket(&s->serveur, "TCP") == 1)
			break;
	}
	return (0);
}

int pasv(char *buffer, int client_fd, t_session *s, t_serveur *serveur)
{
	int port1;
	int port2;
	char *new_msg = NULL;
	char *msg = NULL;

	(void) buffer;
	if (s->mode != NONE)
		close(s->serveur.socket_fd);
	new_msg = get_ip(client_fd, serveur);
	if (new_msg == NULL)
		return (0);
	get_port(s, &port1, &port2);
	asprintf(&msg, "227 Entering Passive Mode (%s,%d,%d)\n",
		new_msg, port1, port2);
	write(client_fd, msg, strlen(msg));
	s->mode = PASV;
	return (0);
}

int port(char *buffer, int client_fd, t_session *session, t_serveur *serveur)
{
	(void) serveur;
	if (strlen(buffer) > 1) {
		session->mode = ACTV;
		write(client_fd, "220 Service ready for new user.\n",
		strlen("220 Service ready for new user.\n"));
	}
	else
		write(client_fd, "999 Failed.\n",
		strlen("999 Failed.\n"));
	return (0);
}
