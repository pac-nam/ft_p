#include "ft_glob_internal.h"

size_t				lst_data_glob_size(t_data_glob *data)
{
	size_t			i;
	t_data_glob		*head;

	head = data->head;
	i = 0;
	while (head)
	{
		head = head->next;
		i++;
	}
	return (i);
}

void				free_glob_lst(t_data_glob **glob)
{
	t_data_glob		*head;
	t_data_glob		*tmp;

	if (!(*glob))
		return ;
	head = (*glob)->head;
	while (head)
	{
		tmp = head;
		head = head->next;
		ft_strdel(&(tmp)->pattern);
		ft_memdel((void *)&(tmp));
	}
}

int					save_res_glob(t_data_glob **glob, char *pattern)
{
	if (!*glob)
	{
		if (!((*glob) = (t_data_glob *)malloc(sizeof(t_data_glob))))
			return (EXIT_FAILURE);
		if (!((*glob)->pattern = ft_strdup(pattern)))
			return (EXIT_FAILURE);
		(*glob)->head = *glob;
		(*glob)->next = NULL;
	}
	else
	{
		if (!((*glob)->next = (t_data_glob *)malloc(sizeof(t_data_glob))))
			return (EXIT_FAILURE);
		if (!((*glob)->next->pattern = ft_strdup(pattern)))
			return (EXIT_FAILURE);
		(*glob)->next->head = (*glob)->head;
		(*glob)->next->next = NULL;
		(*glob) = (*glob)->next;
	}
	return (EXIT_SUCCESS);
}
