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

FILE *connection(t_serveur *sock, t_serveur *client)
{
	FILE *file;

	sock->socket_fd = 0;
	sock->port = client->port;
	sock->ip = client->ip;
	sock->s_in.sin_family = AF_INET;
	sock->s_in.sin_port = htons(0);
	sock->s_in.sin_addr.s_addr = INADDR_ANY;
	if (create_socket(sock, "TCP") == 1)
		return (fprintf(stderr, "Socket failed !\n"), NULL);
	file = fdopen(sock->socket_fd, "rwx");
	if (file == NULL)
		return (fprintf(stderr, "Fdopen failed !\n"), NULL);
	return (file);
}

int get_list(t_serveur *client, FILE *file, char *buff)
{
	char *buffer = NULL;
	size_t size;
	t_serveur sock;
	FILE *new_sock;

	(void) buff;
	new_sock = connection(&sock, client);
	if (new_sock == NULL)
		return (0);
	while (getline(&buffer, &size, new_sock) > 0) {
		write(1, buffer, strlen(buffer));
	}
	getline(&buffer, &size, file);
	write(1, buffer, strlen(buffer));
	return (0);
}

int get_retr(t_serveur *client, FILE *file, char *buff)
{
	char *buffer = NULL;
	size_t size;
	FILE *new_sock;
	t_serveur sock;
	int target_fd;

	(void) client;
	buff[strlen(buff) - 1] = '\0';
	new_sock = connection(&sock, client);
	if (new_sock == NULL)
		return (0);
	target_fd = open(&buff[1], O_WRONLY | O_CREAT, 0644);
	if (target_fd == -1)
		return (0);
	while (getline(&buffer, &size, new_sock) > 0)
		write(target_fd, buffer, strlen(buffer));
	close(target_fd);
	getline(&buffer, &size, file);
	write(1, buffer, strlen(buffer));
	return (0);
}

void finish_stor(FILE *file_to_open, FILE *new_sock, char *buffer, FILE *file)
{
	size_t size;

	fclose(file_to_open);
	fclose(new_sock);
	getline(&buffer, &size, file);
	write(1, buffer, strlen(buffer));
}

int get_stor(t_serveur *client, FILE *file, char *buff)
{
	char *buffer = NULL;
	size_t size;
	FILE *new_sock;
	t_serveur sock;
	FILE *file_to_open;

	(void) client;
	buff[strlen(buff) - 1] = '\0';
	new_sock = connection(&sock, client);
	if (new_sock == NULL)
		return (0);
	file_to_open = fopen(&buff[1], "r");
	if (file_to_open == NULL)
		return (write(1, "500 Command not found.\n",
		strlen("500 Command not found.\n")), 0);
	while (getline(&buffer, &size, file_to_open) > 0)
		write(sock.socket_fd, buffer, strlen(buffer));
	finish_stor(file_to_open, new_sock, buffer, file);
	return (0);
}
