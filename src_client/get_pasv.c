/*
** EPITECH PROJECT, 2018
** mdr
** File description:
** mdr
*/

#include "maccro.h"
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include "serveur.h"

void get_pasv(t_serveur *s, char *buffer, size_t x)
{
	int port1 = 0;
	int port2 = 0;

	for (size_t i = 0; i < strlen(buffer); ++i) {
		if (buffer[i] == ',') {
			buffer[i] = '.';
			x += 1;
		}
		if (x == 4) {
			x = i;
			++i;
			port1 = atoi(&buffer[i]);
			while (buffer[i - 1] != ',')
				++i;
			port2 = atoi(&buffer[i]);
			buffer[x] = '\0';
			asprintf(&s->ip, "%s", buffer);
		}
	}
	s->port = port1 * 256 + port2;
}
