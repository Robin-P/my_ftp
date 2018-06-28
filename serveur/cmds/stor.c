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

int check_stor(char *buffer, int client_fd, t_session *session, int *fd)
{
	buffer[strlen(buffer) - 2] = '\0';
	if (session->mode != PASV)
		return (write(client_fd, "425 Command not found.\n",
			strlen("425 Command not found.\n")), 0);
	write(client_fd,
	"150 File status okay; about to open data connection.\n",
	strlen("150 File status okay; about to open data connection.\n"));
	*fd = data_connection(session);
	if (*fd == -1)
		return (0);
	return (1);
}

void finish_stor(FILE *new_sock, int fd, int target_fd, int client_fd)
{
	fclose(new_sock);
	close(fd);
	close(target_fd);
	write(client_fd, "226 Closing data connection.\n",
	strlen("226 Closing data connection.\n"));
}

int stor(char *buffer, int client_fd, t_session *session, t_serveur *serveur)
{
	char *data = NULL;
	size_t size = 0;
	int fd;
	FILE *new_sock;
	int target_fd;

	(void) serveur;
	check_stor(buffer, client_fd, session, &fd);
	new_sock = fdopen(fd, "rwx");
	target_fd = open(&buffer[1], O_WRONLY | O_CREAT, 0644);
	if (target_fd == -1)
		return (write(client_fd, "226 Closing data connection.\n",
			strlen("226 Closing data connection.\n")), 0);
	while (getline(&data, &size, new_sock) > 0)
		write(target_fd, data, strlen(data));
	finish_stor(new_sock, fd, target_fd, client_fd);
	return (0);
}
