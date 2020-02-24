#include "server.h"

int			connection_refused(t_process *process, int log_fd)
{
	ft_dprintf(log_fd, "connection refused\n");
	send(process->sock_fd_client, CONNECTION_REFUSED,
			ft_strlen(CONNECTION_REFUSED), 0);
	return (0);
}

void		authentification_second(t_process *process, char **tab,
			t_user *list, int log_fd)
{
	t_user	*user;

	process->login = NULL;
	if (!(user = search_user(list, tab[0])))
	{
		ft_free_tab(tab);
		free_user_list(&list);
		ft_dprintf(log_fd, "login not found\n");
		return ;
	}
	if (ft_strcmp(user->password, tab[1]))
	{
		ft_free_tab(tab);
		free_user_list(&list);
		ft_dprintf(log_fd, "wrong password\n");
		return ;
	}
	process->login = ft_strdup(tab[0]);
}

int			authentification(t_process *process, int log_fd, char *pass_file)
{
	char	**tab;
	t_user	*list;

	if (!(tab = ft_strsplit(process->command, ':')))
		return (1);
	if (!tab[0] || !tab[0][0] || !tab[1] || !tab[1][0] || tab[2])
	{
		ft_dprintf(log_fd, "login not well formated\n");
		return (1);
	}
	ft_dprintf(log_fd, "new_connection:\nlogin: %s\npassword:%s\n\n",
	tab[0], tab[1]);
	if (!(list = get_pass_file(pass_file)))
	{
		ft_free_tab(tab);
		return (1);
	}
	authentification_second(process, tab, list, log_fd);
	ft_free_tab(tab);
	free_user_list(&list);
	if (!process->login)
		return (1);
	ft_dprintf(log_fd, "%s connection accepted\n", process->login);
	return (0);
}
