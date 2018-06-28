/*
** EPITECH PROJECT, 2018
** serveur
** File description:
** serveur
*/

#ifndef MY_SERVEUR_H_
# define MY_SERVEUR_H_

typedef enum s_mode {
	NONE,
	PASV,
	ACTV
} t_mode;

typedef struct s_serveur {
	int socket_fd;
	int port;
	char *ip;
	int port_sec;
	struct sockaddr_in s_in;
} t_serveur;

typedef struct s_session {
	int user;
	int pass;
	t_mode mode;
	t_serveur serveur;
} t_session;

typedef struct s_cmds {
	char *name;
	size_t size;
	int (*ptr)(char *cmd, int client_fd, t_session *session,
		t_serveur *serveur);
} t_cmds;

typedef struct s_cmds2 {
	char *name;
	size_t size;
	int (*ptr)(char *cmd, int client_fd, t_session *session);
} t_cmds2;

int create_socket(t_serveur *serveur, char *mod);
int create_client(t_serveur *serveur);
int authentification(int client_fd, char *buffer, t_session *session);
int authentificated(char *buffer, int client_fd, t_session *session,
		t_serveur *serveur);
int noop(char *buffer, int client_fd, t_session *session, t_serveur *serveur);
int quit(char *buffer, int client_fd, t_session *session, t_serveur *serveur);
int help(char *buffer, int client_fd, t_session *session, t_serveur *serveur);
int cwd(char *buffer, int client_fd, t_session *session, t_serveur *serveur);
int cdup(char *buffer, int client_fd, t_session *session, t_serveur *serveur);
int pwd(char *buffer, int client_fd, t_session *session, t_serveur *serveur);
int user(char *buffer, int client_fd, t_session *session, t_serveur *serveur);
int list(char *buffer, int client_fd, t_session *session, t_serveur *serveur);
int user(char *buffer, int client_fd, t_session *session, t_serveur *serveur);
int pasv(char *buffer, int client_fd, t_session *session, t_serveur *serveur);
int retr(char *buffer, int client_fd, t_session *session, t_serveur *serveur);
int stor(char *buffer, int client_fd, t_session *session, t_serveur *serveur);
int port(char *buffer, int client_fd, t_session *session, t_serveur *serveur);
int dele(char *buffer, int client_fd, t_session *session, t_serveur *serveur);
int user_function(char *buffer, int client_fd, t_session *session);
int pass_function(char *buffer, int client_fd, t_session *session);
int quit_function(char *buffer, int client_fd, t_session *session);
int authentificated(char *buffer, int client_fd, t_session *session,
		t_serveur *serveur);
int create_socket(t_serveur *serveur, char *proto_name);
void get_pasv(t_serveur *s, char *buffer, size_t x);
int get_list(t_serveur *client, FILE *file, char *buff);
int get_retr(t_serveur *client, FILE *file, char *buff);
int get_stor(t_serveur *client, FILE *file, char *buff);
int loop(t_serveur *client);
int init_signal();
int check_read(char *buffer);
int data_connection(t_session *session);

#endif /* !MY_SERVEUR_H_ */
