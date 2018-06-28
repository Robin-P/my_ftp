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

int authentificated(char *buffer, int client_fd, t_session *session,
			t_serveur *serveur)
{
	size_t nb = 14;
	static t_cmds cmd_list[] = {
		{"CDUP", strlen("CDUP"), cdup},
		{"PWD", strlen("PWD"), pwd},
		{"CWD", strlen("CWD"), cwd},
		{"NOOP", strlen("NOOP"), noop},
		{"HELP", strlen("HELP"), help},
		{"QUIT", strlen("QUIT"), quit},
		{"USER", strlen("USER"), user},
		{"PASS", strlen("PASS"), user},
		{"PASV", strlen("PASV"), pasv},
		{"PORT", strlen("PORT"), port},
		{"DELE", strlen("DELE"), dele},
		{"LIST", strlen("LIST"), list},
		{"RETR", strlen("RETR"), retr},
		{"STOR", strlen("STOR"), stor}
	};

	for (size_t i = 0; i < nb ; ++i) {
		if (strncmp(buffer, cmd_list[i].name, cmd_list[i].size) == 0)
			return (cmd_list[i].ptr(&buffer[cmd_list[i].size],
						client_fd, session, serveur));
	}
	write(client_fd, "500 Command not found.\n",
		strlen("500 Command not found.\n"));
	return (0);
}

int authentification(int client_fd, char *buffer, t_session *session)
{
	size_t nb = 3;
	static t_cmds2 cmd_list[] = {
		{"USER", strlen("USER"), user_function},
		{"PASS", strlen("PASS"), pass_function},
		{"QUIT", strlen("QUIT"), quit_function}
	};

	for (size_t i = 0 ; i < nb ; ++i) {
		if (strncmp(buffer, cmd_list[i].name, cmd_list[i].size) == 0)
			return (cmd_list[i].ptr(&buffer[cmd_list[i].size],
						client_fd, session));
	}
	write(client_fd, "530 Command not found.\n",
		strlen("530 Command not found.\n"));
	return (0);
}
