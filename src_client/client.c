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

int main(int ac, char **av)
{
	t_serveur client;
	int result = 0;

	if (ac != 3)
		return (fprintf(stderr, "Need two arguments\n"), 1);
	init_signal();
	client.port = atoi(av[2]);
	client.ip = av[1];
	if (create_socket(&client, "TCP") == 1)
		return (84);
	result = loop(&client);
	close(client.socket_fd);
	return (result == 0 ? 84 : 0);
}
