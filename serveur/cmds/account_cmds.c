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

int user(char *buffer, int client_fd, t_session *session, t_serveur *serveur)
{
	(void) serveur;
	(void) session;
	(void) buffer;
	write(client_fd, "530 Already logged\n",
	strlen("530 Already logged\n"));
	return (0);
}

int user_function(char *buffer, int client_fd, t_session *session)
{
	if (strncmp(buffer, " Anonymous", 10) == 0) {
		session->user = 1;
		write(client_fd, "331 User name okay, need password.\n",
		strlen("331 User name okay, need password.\n"));
	}
	else {
		write(client_fd, "331 User name okay, need password.\n",
			strlen("331 User name okay, need password.\n"));
			session->user = 2;
	}
	return (0);
}

int pass_function(char *buffer, int client_fd, t_session *session)
{
	(void) buffer;
	if (session->user == 1) {
		session->pass = 1;
		write(client_fd, "230 User logged in, proceed.\n",
			strlen("230 User logged in, proceed.\n"));
	} else if (session->user == 0)
		write(client_fd, "332 Need account for login.\n",
			strlen("332 Need account for login.\n"));
	else
		write(client_fd, "530 Unknown password\n",
			strlen("530 Unknown password\n"));
	return (0);
}
