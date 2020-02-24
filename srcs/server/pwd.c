#include "server.h"

void	message(t_process *process, char *str)
{
	ft_dprintf(process->log_fd, "send: %s\n", str);
	send(process->sock_fd_client, str, ft_strlen(str), 0);
}

int		return_message(t_process *process, char *str)
{
	message(process, str);
	return (1);
}

void	ft_pwd(t_process *process)
{
	char	*tmp;
	char	str[512];
	ssize_t	len;

	tmp = NULL;
	if (ft_asprintf(&tmp, "%s %d", ACCEPT, ft_strlen(process->pwd)) == -1)
	{
		message(process, COMMAND_FAIL);
		return ;
	}
	message(process, tmp);
	free(tmp);
	if ((len = recv(process->sock_fd_client, str, ft_strlen(ACCEPT), 0)) == -1)
		return ;
	str[len] = '\0';
	if (!ft_strcmp(str, ACCEPT))
		message(process, process->pwd);
	return ;
}
