#ifndef __CLIENT_H
# define __CLIENT_H
# include "ft_p.h"
# include <termios.h>
# include <ctype.h>
# include <string.h>
# define BAD_REQUEST "Bad request"
# define REQUEST_EJECT "[500]: Request was reject by server"
# define PERM_DENIED "Permission denied"
# define IS_DIR "Is a directory"
# define NOT_FOUND "No such file or directory"
# define CMD_SUCCESS "Command okay."
# define CMD_NOT_IMPL "Command not implemented, superfluous at this site."
# define USER_LOGGED "User logged in, proceed."
# define CONNECT_OPEN "Data connection open; no transfer in progress."
# define NEED_ACCOUNT "Need account for login."
# define USER_OK_NOW_PASS "User name okay, need password."
# define EXCEEDED_ALLOC "Exceeded storage allocation (for current"
# define FILE_UNVAILABLE "File unavailable (e.g., file not found, no access)."
# define REQUEST_ABORT "Requested action aborted: local error in processing."

char					*g_login;

typedef struct			s_context
{
	bool				auth;
	char				*login;
	char				*pass;
	int					socket;
	t_env				*env;
}						t_context;

bool					init_prompt(t_context *ctx);
bool					reset_prompt(t_context ctx);
void					print_prompt();
int						handle_client(t_context **ctx);

/*
**	Builtin
*/

int						send_put(char **cmd, t_context *ctx);
int						send_get(char **cmd, t_context *ctx);
int						builtin_cd(char **cmd, t_context *ctx);
int						send_mput(t_context *ctx, char *cmd);
int						send_mget(t_context *ctx, char *cmd);

/*
** Server Builtin
*/

int						server_builtin(char **tab, t_context *ctx);

/*
**	cmd part
*/

int						handle_cmd(char *cmd, t_context *ctx);
int						send_builtin(char **tab);
/*
** User part
*/

int						handle_login(t_context *ctx, char *ip, short port);

/*
**		TOOLS
*/
int						quit(int newline, t_context *ctx);
int						error_handling(int code);
#endif
