#include "server.h"

int		fail(t_process *process)
{
	message(process, COMMAND_FAIL);
	return (1);
}

int		ft_send_file_fd(t_process *process, int fd)
{
	t_stat		stat;
	char		*tmp;
	int			len;

	if ((fstat(fd, &stat)) == -1)
		return (fail(process));
	if (S_ISDIR(stat.st_mode))
	{
		message(process, REFUSE);
		return (1);
	}
	if ((ft_asprintf(&tmp, "%s %064llu", ACCEPT, stat.st_size)) == -1)
		return (fail(process));
	message(process, tmp);
	free(tmp);
	if (!(tmp = (char*)malloc(MAX_SEND)))
		return (fail(process));
	while ((len = read(fd, tmp, MAX_SEND)) > 0)
	{
		tmp[len] = '\0';
		message(process, tmp);
	}
	free(tmp);
	return (0);
}

int		ft_send_file(t_process *process, char *file_name)
{
	int	fd;

	if (verif_access(process, file_name))
	{
		message(process, REFUSE_403);
		return (1);
	}
	if ((fd = open(file_name, O_RDONLY)) < 0)
	{
		ft_printf("file : [%s]\n", file_name);
		message(process, REFUSE_404);
		return (1);
	}
	ft_send_file_fd(process, fd);
	close(fd);
	return (0);
}

int		ft_get(t_process *process, char **command)
{
	char	*file_name;
	int		len;

	if (!command[1] || command[2]
			|| !(file_name = (char*)malloc(ft_atoi(command[1]) + 1)))
		return (fail(process));
	message(process, ACCEPT);
	if ((len = recv(process->sock_fd_client, file_name,
			ft_atoi(command[1]), 0)) == -1)
	{
		free(file_name);
		return (fail(process));
	}
	file_name[len] = '\0';
	ft_send_file(process, file_name);
	free(file_name);
	return (0);
}
