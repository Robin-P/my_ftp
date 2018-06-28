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

int cwd(char *buffer, int client_fd, t_session *session, t_serveur *serveur)
{
	(void) serveur;
	(void) session;
	buffer[strlen(buffer) - 2] = '\0';
	if (strlen(buffer) > 1 && chdir(&buffer[1]) == 0) {
		write(client_fd, "250 Requested file action okay, completed.\n",
		strlen("250 Requested file action okay, completed.\n"));
	} else
		write(client_fd, "550 No directory.\n",
		strlen("550 No directory.\n"));
	return (0);
}

int pwd(char *buffer, int client_fd, t_session *session, t_serveur *serveur)
{
	(void) serveur;
	(void) session;
	(void) buffer;
	write(client_fd, "257 \"", strlen("257 \""));
	write(client_fd, getcwd(NULL, 0), strlen(getcwd(NULL, 0)));
	write(client_fd, "\"\n", strlen("\"\n"));
	return (0);
}

int cdup(char *buffer, int client_fd, t_session *session, t_serveur *serveur)
{
	(void) serveur;
	(void) session;
	(void) buffer;
	if (chdir("..") == 0) {
		write(client_fd, "250 Command okay.\n",
		strlen("250 Command okay.\n"));
	} else
		write(client_fd, "250 Command okay.\n",
		strlen("250 Command okay.\n"));
	return (0);
}
