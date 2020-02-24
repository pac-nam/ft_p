#include "server.h"

void	ft_cd_second(t_process *process, char *folder)
{
	int		verif;

	if ((verif = verif_dir_access(process, folder)) == 403)
	{
		message(process, REFUSE_403);
		return ;
	}
	else if (verif == 404)
	{
		message(process, REFUSE_404);
		return ;
	}
	else if (verif)
	{
		message(process, REFUSE);
		return ;
	}
	chdir(folder);
	free(process->pwd);
	process->pwd = getcwd(NULL, 0);
	message(process, ACCEPT);
}

void	ft_cd(t_process *process, char **command)
{
	char	*dir_name;

	if (!command[1] || command[2]
			|| !(dir_name = ft_strnew(ft_atoi(command[1]) + 1)))
	{
		message(process, COMMAND_FAIL);
		return ;
	}
	message(process, ACCEPT);
	if ((recv(process->sock_fd_client, dir_name, ft_atoi(command[1]), 0)) == -1)
	{
		free(dir_name);
		message(process, COMMAND_FAIL);
		return ;
	}
	ft_cd_second(process, dir_name);
	free(dir_name);
	return ;
}
