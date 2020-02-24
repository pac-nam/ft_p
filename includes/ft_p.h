#ifndef __FT_P_H
# define __FT_P_H

# include "ft_printf.h"
# include "ft_glob.h"
# include <fcntl.h>
# include <sys/socket.h>
# include <netdb.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <time.h>
# include <stdio.h>
# include <arpa/inet.h>
# include <errno.h>
# include <termios.h>
# include <openssl/opensslconf.h>
# include <openssl/crypto.h>
# include <openssl/sha.h>
# include <openssl/opensslv.h>
# include <stdbool.h>

# define SOCKET_ERROR "ERROR: sock_fd creation failed\n"
# define BIND_ERROR "ERROR: binding error\n"
# define PORT_DIGIT_ERROR "ERROR: port should have only digits\n"
# define PORT_ERROR "ERROR: port max is 65535\n"
# define LISTEN_ERROR "ERROR: Listen error\n"
# define BAD_LOGIN "login can not be longer than 200 char and lower than 1\n"
# define BAD_PASS "password can not be longer than 200 char and lower than 1\n"
# define BAD_LCHAR "ERROR: login can not contain char ':' or '\\n'\n"
# define BAD_PCHAR "ERROR: password can not contain char ':' or '\\n'\n"
# define CONNECTION_REFUSED "connection refused"
# define CONNECTION_ACCEPTED "connection accepted"
# define UNKNOW_COMMAND "unknow command"
# define COMMAND_FAIL "command fail"
# define COMMAND_SUCCESS "command success"
# define WHITE "\x1b[37;1m"
# define RESET "\x1b[0m"
# define ACCEPT "accept"
# define CONTINUE "continue"
# define REFUSE "refuse"
# define REFUSE_403 "refuse 403"
# define REFUSE_404 "refuse 404"
# define ERROR_500 "error 500"
# define MAX_SEND 1000000

typedef struct sockaddr_in	t_sockaddr;
typedef	struct stat			t_stat;
typedef struct termios		t_termios;

typedef struct				s_env
{
	char					*name;
	char					*value;
	struct s_env			*head;
	struct s_env			*next;
}							t_env;

char						*get_login(void);
char						*get_password(void);
char						*sha512(char *str);
int							set_env(t_env **ctx, char **env);
char						*ft_getenv(char *search, t_env *env);
void						free_env(t_env **env);
int							ft_setnewpwd(char *newpwd, t_env *env);
#endif
