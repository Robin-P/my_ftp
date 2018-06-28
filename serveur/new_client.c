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

void init_session(t_session *s)
{
	s->user = 0;
	s->pass = 0;
	s->mode = NONE;
	s->serveur.socket_fd = 0;
	s->serveur.port = 0;
	s->serveur.s_in.sin_family = AF_INET;
	s->serveur.s_in.sin_port = htons(0);
	s->serveur.s_in.sin_addr.s_addr = INADDR_ANY;
}

int choose_authent(t_serveur *serveur, int client_fd, char *buffer,
		t_session *session)
{
	if (session->user == 0 || session->pass == 0) {
		if (authentification(client_fd, buffer, session) == 1)
			return (1);
	}
	else if (authentificated(buffer, client_fd,
				session, serveur) == 1) {
		session->user = 0;
		session->pass = 0;
	}
	return (0);
}

int process_client(int client_fd, t_serveur *serveur)
{
	FILE *file;
	char *buffer = NULL;
	size_t size;
	t_session session;

	init_session(&session);
	file = fdopen(client_fd, "rwx");
	if (file == NULL)
		return (fprintf(stderr, "Fdopen failed !\n"), 0);
	while (getline(&buffer, &size, file) > 0) {
		if (choose_authent(serveur, client_fd, buffer, &session) == 1)
			break;
	}
	return (1);
}

int accept_create(t_serveur *serveur)
{
	int client_fd;
	struct sockaddr_in s_in_client;
	socklen_t s_in_size;

	s_in_size = sizeof(s_in_client);
	client_fd = accept(serveur->socket_fd,
			(struct sockaddr *)&s_in_client, &s_in_size);
	if (client_fd == -1)
		return (fprintf(stderr, "Accept client failed\n"), -1);
	return (client_fd);
}

int create_client(t_serveur *serveur)
{
	int pid;
	int client_fd;

	client_fd = accept_create(serveur);
	if (client_fd == -1)
		return (0);
	pid = fork();
	if (pid == -1)
		return (fprintf(stderr, "Fork failed\n"), 0);
	else if (pid == 0) {
		process_client(client_fd, serveur);
		close(client_fd);
		exit(0);
	}
	write(client_fd, "220 Service ready for new user.\n",
	strlen("220 Service ready for new user.\n"));
	close(client_fd);
	return (1);
}