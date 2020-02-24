#include "server.h"

static void		ft_put_third(int new_file, t_process *process,
				uint64_t file_len, char *buf)
{
	int			len;

	while (file_len != 0)
	{
		message(process, ACCEPT);
		if (file_len > MAX_SEND)
		{
			if ((len = recv(process->sock_fd_client, buf, MAX_SEND, 0) == -1))
			{
				message(process, COMMAND_FAIL);
				return ;
			}
		}
		else
		{
			if ((len = recv(process->sock_fd_client, buf, file_len, 0)) == -1)
			{
				message(process, COMMAND_FAIL);
				return ;
			}
		}
		write(new_file, buf, len);
		file_len -= (unsigned long long)len;
	}
	message(process, ACCEPT);
}

static void		ft_put_second(int new_file, t_process *process,
				uint64_t file_len)
{
	char		*buf;

	if (!(buf = (char*)malloc(MAX_SEND)))
	{
		message(process, COMMAND_FAIL);
		return ;
	}
	ft_put_third(new_file, process, file_len, buf);
	free(buf);
}

void			ft_put_first(t_process *process,
				char **command, char *file_name)
{
	int			new_file;

	if ((recv(process->sock_fd_client, file_name,
			ft_atoi(command[1]), 0)) == -1)
	{
		message(process, COMMAND_FAIL);
		return ;
	}
	if (verif_access(process, file_name))
	{
		message(process, REFUSE_403);
		return ;
	}
	if ((new_file = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644)) < 0)
	{
		message(process, COMMAND_FAIL);
		return ;
	}
	ft_put_second(new_file, process, ft_atoull(command[2]));
	close(new_file);
}

void			ft_put(t_process *process, char **command)
{
	char		*file_name;

	if (!command[1] || !command[2] || command[3]
			|| !(file_name = ft_strnew(ft_atoi(command[1]) + 1)))
	{
		message(process, COMMAND_FAIL);
		return ;
	}
	message(process, ACCEPT);
	ft_put_first(process, command, file_name);
	free(file_name);
}
