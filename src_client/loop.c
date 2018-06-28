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

void case_data(t_serveur *client, FILE *file, char *prev_buff, int cmd)
{
	switch (cmd) {
	case 0:
		get_list(client, file, &prev_buff[4]);
		break;
	case 1:
		get_retr(client, file, &prev_buff[4]);
		break;
	case 2:
		get_stor(client, file, &prev_buff[4]);
		break;
	}
}

int lopo_next(t_serveur *client, FILE *file, char *buff)
{
	static char *prev_buff = NULL;
	size_t size;
	static int cmd = 0;

	if (strlen(buff) >= 4 && strncmp(buff, "221", 3) == 0)
		return (1);
	else if (strlen(buff) >= 4 && strncmp(buff, "227", 3) == 0)
		get_pasv(client, &buff[27], 0);
	if (strlen(buff) >= 4 && strncmp(buff, "150", 3) == 0)
		case_data(client, file, prev_buff, cmd);
	getline(&buff, &size, stdin);
	prev_buff = strdup(buff);
	if (strncmp(buff, "LIST", 4) == 0)
		cmd = 0;
	else if (strncmp(buff, "RETR", 4) == 0)
		cmd = 1;
	else if (strncmp(buff, "STOR", 4) == 0)
		cmd = 2;
	write(client->socket_fd, buff, strlen(buff));
	return (0);
}

int loop(t_serveur *client)
{
	FILE *file;
	char *buff = NULL;
	size_t size;
	int state = 0;

	file = fdopen(client->socket_fd, "rwx");
	if (file == NULL)
		return (fprintf(stderr, "Fdopen failed !\n"), 0);
	while (g_loop == 0) {
		if (state == 1) {
			if (lopo_next(client, file, buff) == 1)
				break;
			state = 0;
		} else {
			getline(&buff, &size, file);
			write(1, buff, strlen(buff));
			state = check_read(buff);
		}
	}
	return (1);
}
