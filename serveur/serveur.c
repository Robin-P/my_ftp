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

int g_loop = 0;

int server_running(t_serveur *serveur)
{
	while (g_loop == 0)
		create_client(serveur);
	return (1);
}

void ctrlc(int s)
{
	(void) s;
	g_loop = 1;
}

int init_signal(void)
{
	struct sigaction sigIntHandler;

	sigIntHandler.sa_handler = ctrlc;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;
	sigaction(SIGINT, &sigIntHandler, NULL);
	return 0;
}

int usage(int nb)
{
	printf("USAGE: ./server port path\n");
	printf("\tport\tis the port number on which the server socket listens");
	printf("\n\tpath\tis the path to the home directory for the Anonymous");
	printf(" user\n");
	return (nb);
}

int main(int ac, char **av)
{
	t_serveur serveur;
	int result;

	if (ac != 3)
		return (usage(84));
	else if (ac == 2 &&
		(strcmp(av[1], "-h") == 0 || strcmp(av[1], "-help") == 0))
		return (usage(0));
	if (chdir(av[2]) == -1)
		return (fprintf(stderr, "Error bad path\n"), 84);
	init_signal();
	serveur.port = atoi(av[1]);
	if (create_socket(&serveur, "TCP") == 0)
		return (84);
	result = server_running(&serveur);
	close(serveur.socket_fd);
	return (result == 0 ? 84 : 0);
}
