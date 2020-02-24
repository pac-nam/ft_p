#include "server.h"

int		ft_dispatcher(t_process *process, char **command)
{
	if (!command[1] && !ft_strcmp(command[0], "pwd"))
		ft_pwd(process);
	else if (!command[1] && !ft_strcmp(command[0], "quit"))
	{
		ft_quit(process);
		return (1);
	}
	else if (!ft_strcmp(command[0], "cd") && command[1])
		ft_cd(process, command);
	else if (!ft_strcmp(command[0], "ls") && command[1])
		ft_ls(process, command);
	else if (!ft_strcmp(command[0], "get") && command[1])
		ft_get(process, command);
	else if (!ft_strcmp(command[0], "put") && command[1])
		ft_put(process, command);
	else if (!ft_strcmp(command[0], "mkdir") && command[1])
		ft_mkdir(process, command);
	else if (!ft_strcmp(command[0], "mget") && command[1])
		ft_mget(process, command);
	else
		message(process, UNKNOW_COMMAND);
	return (0);
}

void	client_command_loop_second(t_process *process, char **tab)
{
	ssize_t	len;

	if ((len = recv(process->sock_fd_client,
			process->command, 512, 0)) == -1)
	{
		ft_dprintf(process->log_fd,
				"ERROR: recv fail, user have probably logout\n");
		return ;
	}
	(process->command)[len] = '\0';
	ft_dprintf(process->log_fd, "%s\n", process->command);
	if (!(tab = ft_strsplit(process->command, ' ')))
	{
		ft_dprintf(process->log_fd, "ERROR: strsplit failt\n");
		return ;
	}
	if (ft_dispatcher(process, tab))
		return ;
}

void	client_command_loop(t_process *process)
{
	char	**tab;

	tab = NULL;
	while (1)
	{
		ft_bzero(process->command, 512);
		ft_dprintf(process->log_fd, "waiting command...\n");
		client_command_loop_second(process, tab);
		if (tab)
		{
			ft_free_tab(tab);
			tab = NULL;
		}
	}
}
