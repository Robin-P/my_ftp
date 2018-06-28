/*
** EPITECH PROJECT, 2018
** mdr
** File description:
** mdr
*/

#include <stdio.h>
#include <sys/types.h>
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

int noop(char *buffer, int client_fd, t_session *session, t_serveur *serveur)
{
	(void) serveur;
	(void) session;
	(void) buffer;
	write(client_fd, "200 Command okay.\n", strlen("200 Command okay.\n"));
	return (0);
}

int help(char *buffer, int client_fd, t_session *session, t_serveur *serveur)
{
	(void) serveur;
	(void) session;
	(void) buffer;
	write(client_fd, "214 Help message.\n", strlen("214 Help message.\n"));
	return (0);
}

int quit(char *buffer, int client_fd, t_session *session, t_serveur *serveur)
{
	(void) serveur;
	(void) session;
	(void) buffer;
	if (session->mode != NONE) {
		if (close(session->serveur.socket_fd) == -1)
			return (fprintf(stderr, "Close failed\n"), 0);
	}
	write(client_fd, "221 Logged out.\n", strlen("221 Logged out.\n"));
	return (1);
}

int quit_function(char *buffer, int client_fd, t_session *session)
{
	(void) buffer;
	(void) session;
	write(client_fd, "221 Service closing control connection.\n",
		strlen("221 Service closing control connection.\n"));
	return (1);
}

int dele(char *buffer, int client_fd, t_session *session, t_serveur *serveur)
{
	(void) serveur;
	(void) session;
	if (strlen(buffer) > 1) {
		buffer[strlen(buffer) - 2] = '\0';
		if (remove(&buffer[1]) == -1) {
			write(client_fd, "550 Failed.\n",
			strlen("550 Failed.\n"));
			return (0);
		}
		write(client_fd, "250 Requested file action okay, completed.\n",
		strlen("250 Requested file action okay, completed.\n"));
		return (0);
	}
	write(client_fd, "550 Failed.\n",
	strlen("550 Failed.\n"));
	return (0);
}
