#include "server.h"

void			ft_mkdir_second(t_process *process,
				char **command, char *new_dir_name)
{
	if ((recv(process->sock_fd_client, new_dir_name,
			ft_atoi(command[1]), 0)) == -1)
	{
		message(process, COMMAND_FAIL);
		return ;
	}
	if (verif_access(process, new_dir_name))
	{
		message(process, REFUSE_403);
		return ;
	}
	if (mkdir(new_dir_name, 0755) && errno != EEXIST)
	{
		message(process, COMMAND_FAIL);
		return ;
	}
	message(process, ACCEPT);
}

void			ft_mkdir(t_process *process, char **command)
{
	char	*new_dir_name;

	if (!command[1] || command[2]
			|| !(new_dir_name = ft_strnew(ft_atoi(command[1]) + 1)))
	{
		message(process, COMMAND_FAIL);
		return ;
	}
	message(process, ACCEPT);
	ft_mkdir_second(process, command, new_dir_name);
	free(new_dir_name);
}
