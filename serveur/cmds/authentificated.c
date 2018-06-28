/*
** EPITECH PROJECT, 2018
** mdr
** File description:
** mdr
*/

#include "maccro.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include "serveur.h"

int data_connection(t_session *session)
{
	struct sockaddr_in s_in_client;
	socklen_t s_in_size;
	int fd = 0;

	s_in_size = sizeof(s_in_client);
	fd = accept(session->serveur.socket_fd,
			(struct sockaddr *)&s_in_client, &s_in_size);
	if (fd == -1)
		return (fprintf(stderr, "Accept client failed\n"), -1);
	return (fd);
}

int get_line_list(char *buffer, int fd, int client_fd)
{
	FILE *file;
	char path[1024];

	buffer[strlen(buffer) - 2] = '\0';
	asprintf(&buffer, "ls -l%s | sed 1d", buffer);
	file = popen(buffer, "r");
	if (file == NULL)
		return (write(client_fd, "552 Command not found.\n",
			strlen("552 Command not found.\n")), 0);
	while (fgets(path, sizeof(path) - 1, file) != NULL)
		write(fd, path, strlen(path));
	pclose(file);
	return (0);
}

int list(char *buffer, int client_fd, t_session *session, t_serveur *serveur)
{
	int fd;

	(void) buffer;
	(void) serveur;
	if (session->mode != PASV)
		return (write(client_fd, "425 Command not found.\n",
			strlen("425 Command not found.\n")), 0);
	write(client_fd,
	"150 File status okay; about to open data connection.\n",
	strlen("150 File status okay; about to open data connection.\n"));
	fd = data_connection(session);
	if (fd == -1)
		return (0);
	get_line_list(buffer, fd, client_fd);
	write(client_fd, "226 Closing data connection.\n",
		strlen("226 Closing data connection.\n"));
	close(fd);
	return (0);
}

int check_retr(char *buffer, int client_fd, t_session *session, FILE **file)
{
	buffer[strlen(buffer) - 2] = '\0';
	if (session->mode != PASV)
		return (write(client_fd, "425 Command not found.\n",
			strlen("425 Command not found.\n")), 0);
	*file = fopen(&buffer[1], "rwx");
	if (*file == NULL) {
		return (write(client_fd, "550 Failed to open file.\n",
			strlen("550 Failed to open file.\n")), 0);
	}
	write(client_fd,
	"150 File status okay; about to open data connection.\n",
	strlen("150 File status okay; about to open data connection.\n"));
	return (1);
}

int retr(char *buffer, int client_fd, t_session *session, t_serveur *serveur)
{
	FILE *file = NULL;
	char *data = NULL;
	size_t size = 0;
	int fd;

	(void) serveur;
	if (check_retr(buffer, client_fd, session, &file) == 0)
		return (0);
	fd = data_connection(session);
	if (fd == -1)
		return (0);
	while (getline(&data, &size, file) > 0)
		write(fd, data, strlen(data));
	fclose(file);
	close(fd);
	write(client_fd, "226 Closing data connection.\n",
	strlen("226 Closing data connection.\n"));
	return (0);
}