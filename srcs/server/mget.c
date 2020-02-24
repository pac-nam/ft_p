#include "server.h"

void			ft_mget_third(t_process *process, char *nb, char *file)
{
	ft_bzero(nb, 64);
	ft_sprintf(nb, "%064llu", ft_strlen(file));
	message(process, nb);
	message(process, file);
	ft_send_file(process, file);
}

void			ft_mget_second(t_process *process,
unsigned long long size, char *str)
{
	t_glob	glob;
	char	nb[65];
	char	**tmp;

	if ((recv(process->sock_fd_client, str, size, 0)) == -1)
	{
		message(process, COMMAND_FAIL);
		return ;
	}
	str[size] = '\0';
	if (ft_glob(str, &glob))
	{
		message(process, COMMAND_FAIL);
		return ;
	}
	ft_sprintf(nb, "%064llu", glob.size);
	message(process, nb);
	tmp = glob.res;
	while (*tmp)
	{
		ft_mget_third(process, nb, &((*tmp)[5]));
		tmp += 1;
	}
	ft_globfree(&glob);
}

void			ft_mget(t_process *process, char **command)
{
	char		*str;
	ssize_t		size;

	size = ft_atoull(command[1]);
	if (!(str = ft_strnew(size + 1)))
	{
		message(process, COMMAND_FAIL);
		return ;
	}
	message(process, ACCEPT);
	ft_mget_second(process, size, str);
	free(str);
}
