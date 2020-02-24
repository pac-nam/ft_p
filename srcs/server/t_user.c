#include "server.h"

void		free_user_list(t_user **list)
{
	t_user	*tmp;

	if (!list || !(*list))
		return ;
	while ((tmp = (*list)->next))
	{
		ft_strdel(&((*list)->login));
		ft_strdel(&((*list)->password));
		free(*list);
		*list = tmp;
	}
	ft_strdel(&((*list)->login));
	ft_strdel(&((*list)->password));
	free(*list);
	*list = NULL;
}

void		free_elem(t_user *to_delete)
{
	if (to_delete)
	{
		if (to_delete->login)
			free(to_delete->login);
		if (to_delete->password)
			free(to_delete->password);
		free(to_delete);
	}
}

void		remove_elem(t_user **list, t_user *to_delete)
{
	t_user	*tmp;

	tmp = *list;
	if (tmp == to_delete)
	{
		*list = (*list)->next;
		free_elem(to_delete);
		return ;
	}
	while (tmp->next && tmp->next != to_delete)
		tmp = tmp->next;
	if (tmp->next)
	{
		tmp->next = tmp->next->next;
		free_elem(to_delete);
	}
}

int			add_elem(t_user **list, char *login, char *password)
{
	t_user	*elem;

	if (!(elem = (t_user*)malloc(sizeof(t_user))))
		return (1);
	if (!(elem->login = ft_strdup(login)))
	{
		free(elem);
		return (1);
	}
	if (!(elem->password = ft_strdup(password)))
	{
		free(elem->login);
		free(elem);
		return (1);
	}
	elem->next = *list;
	*list = elem;
	return (0);
}
