#include "server.h"

t_process		*ret_free_process(t_process *process)
{
	free_process(process);
	return (NULL);
}

t_process		*new_process(t_context *ctx, int log_fd)
{
	t_process	*process;

	ft_dprintf(log_fd, "new_process\n");
	if (!(process = (t_process*)malloc(sizeof(t_process))))
	{
		ft_dprintf(log_fd, "ERROR: malloc error\n");
		return (NULL);
	}
	process->pwd = NULL;
	process->root = NULL;
	process->login = NULL;
	process->tmp_file = NULL;
	if ((ft_asprintf(&process->log_file, "%s/", ctx->log_folder)) == -1
	|| (ft_asprintf(&process->pwd, "%s/", ctx->root)) == -1)
		process->command_len = sizeof(t_sockaddr);
	if ((process->sock_fd_client = accept(ctx->sock_fd_server,
	(struct sockaddr *)&(process->sockaddr_client),
	&(process->command_len))) == -1)
		return (ret_free_process(process));
	if ((recv(process->sock_fd_client, process->command, 512, 0)) == -1)
		return (ret_free_process(process));
	return (process);
}

void			free_process(t_process *process)
{
	if (process)
	{
		ft_strdel(&process->pwd);
		ft_strdel(&process->root);
		ft_strdel(&process->login);
		ft_strdel(&process->log_file);
		ft_strdel(&process->tmp_file);
		close(process->sock_fd_client);
		free(process);
	}
}

int				open_log_fd(t_context *ctx, int *fd)
{
	char		*tmp;

	if (!(tmp = ft_strjoin("/", GLOBAL_LOGS)))
	{
		printf("ERROR: strjoin fail\n");
		return (1);
	}
	if (!(tmp = ft_strjoinfree(ctx->log_folder, tmp, 2)))
	{
		printf("ERROR: strjoinfree fail\n");
		return (1);
	}
	if ((*fd = open(tmp, O_CREAT | O_WRONLY | O_TRUNC, 0755)) < 0)
	{
		printf("ERROR: can not write in %s\n", tmp);
		return (1);
	}
	return (0);
}

int				server(t_context *ctx)
{
	t_process	*process;
	int			process_id;
	int			log_fd;

	if (open_log_fd(ctx, &log_fd))
		return (1);
	while (1)
	{
		process = NULL;
		if (!(process = new_process(ctx, log_fd)))
			return (1);
		if (!authentification(process, log_fd, ctx->pass_file))
		{
			process_id = fork();
			if (process_id < 0)
				ft_dprintf(log_fd, "ERROR: fork fail\n");
			else if (process_id == 0)
				return (connection_accepted(process, log_fd));
		}
		else
			connection_refused(process, log_fd);
		free_process(process);
	}
	close(log_fd);
	return (0);
}
