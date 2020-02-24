#include "server.h"

t_user		*get_pass_file_line(char *pass_file, t_user *list,
			char **tab, char *line)
{
	if (tab)
		free(tab);
	if (!(tab = ft_strsplit(line, ':')))
	{
		ft_dprintf(2, "ERROR: strsplit error\n");
		free(line);
		free_user_list(&list);
		return (NULL);
	}
	ft_strdel(&line);
	if (!tab[0])
		return (list);
	if (!tab[1] || tab[2])
	{
		ft_free_tab(tab);
		ft_dprintf(2, "ERROR: %s file corrupted\n", pass_file);
		free_user_list(&list);
		return (NULL);
	}
	if (add_elem(&list, tab[0], tab[1]))
	{
		free_user_list(&list);
		return (NULL);
	}
	return (list);
}

t_user		*get_pass_file(char *pass_file)
{
	char	*line;
	char	**tab;
	int		pass_fd;
	t_user	*list;

	list = NULL;
	tab = NULL;
	if ((pass_fd = open(pass_file, O_CREAT | O_RDONLY, 0755)) < 0)
	{
		printf("ERROR: can not create or read %s\n", pass_file);
		return (NULL);
	}
	if (add_elem(&list, "", ""))
	{
		printf("ERROR: can not create user list\n");
		return (NULL);
	}
	while ((ft_gnl(pass_fd, &line)) > 0)
	{
		if (!(list = get_pass_file_line(pass_file, list, tab, line)))
			return (NULL);
	}
	close(pass_fd);
	return (list);
}

static int	write_in_pass_file(t_user *list, char *pass_file)
{
	t_user	*tmp;
	int		p_fd;

	if ((p_fd = open(pass_file, O_CREAT | O_WRONLY | O_TRUNC, 0755)) < 0)
	{
		ft_dprintf(2, "ERROR: can not write in %s\n", pass_file);
		return (1);
	}
	tmp = list;
	while (tmp)
	{
		ft_dprintf(p_fd, "%s:%s\n", tmp->login, tmp->password);
		tmp = tmp->next;
	}
	close(p_fd);
	return (0);
}

int			add_in_pass_file(char *login, char *pass,
			char *pass_file, t_user **list)
{
	int		p_fd;
	t_user	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (!ft_strcmp(tmp->login, login))
		{
			ft_dprintf(2, "ERROR: %s login already used\n", login);
			return (1);
		}
		tmp = tmp->next;
	}
	if (add_elem(list, login, pass))
		return (ft_dprintf(2, "ERROR: can not add %s to users\n", login) && 0);
	if ((p_fd = open(pass_file, O_CREAT | O_WRONLY | O_APPEND, 0755)) < 0)
	{
		ft_dprintf(2, "ERROR: can not write in %s\n", pass_file);
		return (1);
	}
	ft_dprintf(p_fd, "%s:%s\n", login, pass);
	close(p_fd);
	return (0);
}

int			remove_from_pass_file(char *login, char *pass,
			char *pass_file, t_user **list)
{
	t_user	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (!ft_strcmp(tmp->login, login) && !ft_strcmp(tmp->password, pass))
		{
			remove_elem(list, tmp);
			return (write_in_pass_file(*list, pass_file));
		}
		tmp = tmp->next;
	}
	ft_dprintf(2, "ERROR: wrong user or password\n");
	return (1);
}
