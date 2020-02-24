#include "server.h"

void	ft_ls_third(t_process *process, char *path)
{
	int fd;

	if ((fd = open(process->tmp_file,
	O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1
	|| dup2(fd, 1) == -1
	|| (execl("/bin/sh", "/bin/sh", "-c", "ls", path, NULL)) == -1)
	{
		dup2(1, fd);
		close(fd);
		execl("/bin/rm", "/bin/rm", "-f", process->tmp_file, NULL);
		exit(1);
	}
	dup2(1, fd);
	close(fd);
	exit(0);
}

int		ft_ls_second(t_process *process, char **command, char *path)
{
	int		pid;
	int		fd;

	if ((recv(process->sock_fd_client, path, ft_atoi(command[1]), 0)) == -1)
		return (return_message(process, COMMAND_FAIL));
	if (verif_dir_access(process, path) && verif_access(process, path))
		return (return_message(process, REFUSE_403));
	if ((pid = fork()) == -1)
		return (return_message(process, REFUSE_403));
	else if (!pid)
		ft_ls_third(process, path);
	else
		wait4(0, NULL, 0, NULL);
	if ((fd = open(process->tmp_file, O_RDONLY)) < 0)
		return (return_message(process, COMMAND_FAIL));
	ft_send_file_fd(process, fd);
	close(fd);
	return (0);
}

int		ft_ls(t_process *process, char **command)
{
	char	*name;
	int		ret;

	if (!command[1] || command[2]
			|| !(name = ft_strnew(ft_atoi(command[1]) + 1)))
	{
		message(process, COMMAND_FAIL);
		return (1);
	}
	message(process, ACCEPT);
	ret = ft_ls_second(process, command, name);
	free(name);
	return (ret);
}
