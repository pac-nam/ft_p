#include "server.h"

int				end_process(int to_return, t_process *process)
{
	free_process(process);
	return (to_return);
}

int				open_process_log_file(t_process *process, int log_fd)
{
	char		*log_file;
	time_t		time_var;
	char		*tmp;

	time_var = time(NULL);
	if (!(log_file = ctime(&time_var)))
		return (1);
	if (!(log_file = ft_strsub(log_file, 4, 20)))
		return (2);
	if ((ft_asprintf(&(process->tmp_file), "%s.%s_tmp",
	process->log_file, process->login) == -1)
	|| (ft_asprintf(&tmp, "%s%s%s", process->log_file,
	process->login, log_file)) == -1)
	{
		free(log_file);
		ft_dprintf(log_fd, "ERROR: ft_asprintf fail\n");
		return (3);
	}
	free(log_file);
	free(process->log_file);
	process->log_file = tmp;
	if (!(process->log_fd = open(process->log_file,
			O_CREAT | O_WRONLY | O_TRUNC, 0755)))
		return (6);
	return (0);
}

int				init_process_root(t_process *process)
{
	if ((ft_asprintf(&process->root, "%s%s/",
			process->pwd, process->login)) == -1)
		return (1);
	if (mkdir(process->root, 0755) && errno != EEXIST)
		return (1);
	if (chdir(process->root))
		return (1);
	free(process->pwd);
	if (!(process->pwd = getcwd(NULL, 0)))
		return (1);
	ft_dprintf(process->log_fd, "root: %s\n", process->root);
	return (0);
}

int				connection_accepted(t_process *process, int log_fd)
{
	if (open_process_log_file(process, log_fd) || init_process_root(process))
	{
		connection_refused(process, log_fd);
		return (end_process(1, process));
	}
	send(process->sock_fd_client, CONNECTION_ACCEPTED,
			ft_strlen(CONNECTION_ACCEPTED), 0);
	client_command_loop(process);
	return (end_process(0, process));
}
