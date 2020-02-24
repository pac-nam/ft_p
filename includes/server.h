#ifndef __SERVER_H
# define __SERVER_H
# include "ft_p.h"

# define BACKLOG 1
# define SERVER_FOLDER "server_folder"
# define SERVER_LOGS "logs"
# define GLOBAL_LOGS "global_logs"
# define USER_FOLDER "user"
# define PASSWORDS ".passwords"

typedef struct		s_user
{
	char			*login;
	char			*password;
	struct s_user	*next;
}					t_user;

typedef struct		s_context
{
	uint16_t		port;
	char			*root;
	char			*pass_file;
	char			*log_folder;
	char			*error;
	t_sockaddr		sockaddr_server;
	int				sock_fd_server;
	t_user			*user_list;
	int				end;
}					t_context;

typedef struct		s_process
{
	char			*pwd;
	char			*root;
	char			*login;
	char			*log_file;
	char			*tmp_file;
	int				log_fd;
	t_sockaddr		sockaddr_client;
	int				sock_fd_client;
	char			command[512];
	unsigned int	command_len;
}					t_process;

int		authentification(t_process *process, int log_fd, char *pass_file);
int		connection_accepted(t_process *process, int log_fd);
int		connection_refused(t_process *process, int log_fd);
int		init_struct(char *str, t_context *ctx);
int		server(t_context *ctx);
int		keep_hand_on_server(t_context *ctx);
int		add_elem(t_user **list, char *login, char *password);
void	remove_elem(t_user **list, t_user *to_delete);
void	free_user_list(t_user **list);
void	newuser(t_context *ctx);
void	deleteuser(t_context *ctx);
void	showuser(t_user *list);
t_user	*search_user(t_user *list, char *login);
t_user	*get_pass_file(char *pass_file);
int		add_in_pass_file(char *login, char *pass, char *pass_file, t_user **list);
int		remove_from_pass_file(char *login, char *pass, char *pass_file, t_user **list);
int		verif_access(t_process *process, char *file);
int		verif_dir_access(t_process *process, char *folder);
void	free_process(t_process *process);
void	client_command_loop(t_process *process);
void	message(t_process *process, char *str);
void	ft_pwd(t_process *process);
void	ft_cd(t_process *process, char **command);
int		ft_ls(t_process *process, char **command);
int		ft_get(t_process *process, char **command);
int		ft_send_file(t_process *process, char *file_name);
int		ft_send_file_fd(t_process *process, int fd);
void	ft_mkdir(t_process *process, char **command);
void	ft_mget(t_process *process, char **command);
void	ft_put(t_process *process, char **command);
void	ft_quit(t_process *process);
int		return_message(t_process *process, char *str);

#endif