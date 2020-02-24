#include "ft_glob.h"
#include "ft_glob_internal.h"

static int			set_glob(char **res, t_glob *glob)
{
	if (!(glob->res = ft_tabdup(res)))
		return (EXIT_FAILURE);
	glob->size = ft_tablen(res);
	return (EXIT_SUCCESS);
}

static char			**set_glob_tab(t_data_glob *head, size_t len)
{
	char			**tab;
	size_t			i;

	i = 0;
	if (!(tab = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	ft_bzero(tab, len + 1);
	while (head)
	{
		if (!(tab[i] = ft_strdup(head->pattern)))
			return (NULL);
		i++;
		head = head->next;
	}
	tab[i] = 0;
	return (tab);
}

static char			**transform_lst_to_tab(t_data_glob *data)
{
	char			**tab;
	t_data_glob		*head;
	size_t			len;

	if (!data)
	{
		ft_dprintf(2, "No match found\n");
		return (NULL);
	}
	head = data->head;
	len = lst_data_glob_size(data);
	if (!(tab = set_glob_tab(head, len)))
		return (NULL);
	if (!ft_tablen(tab))
	{
		ft_dprintf(2, "No match found\n");
		free_glob_lst(&data);
		ft_free_tab(tab);
		return (NULL);
	}
	free_glob_lst(&data);
	return (tab);
}

static char			**parse_glob(char ***tab, size_t len, t_data_glob *data)
{
	size_t			i;

	i = 0;
	while (++i < len)
	{
		if (ft_strchr((*tab)[i], '*'))
		{
			if (start_glob((*tab)[0], (*tab)[i], &data))
			{
				ft_free_tab((*tab));
				return (NULL);
			}
		}
		else
		{
			if (save_res_glob(&data, (*tab)[i]))
			{
				ft_free_tab((*tab));
				return (NULL);
			}
		}
	}
	ft_free_tab((*tab));
	return (transform_lst_to_tab(data));
}

int					ft_glob(char *pattern, t_glob *glob)
{
	char			**res;
	char			**tab;
	size_t			len;
	t_data_glob		*data;

	data = NULL;
	if (!(tab = ft_strsplit(pattern, ' ')))
		return (EXIT_FAILURE);
	len = ft_tablen(tab);
	if (!(res = parse_glob(&tab, len, data)))
		return (EXIT_FAILURE);
	if (set_glob(res, glob))
	{
		ft_free_tab(res);
		return (EXIT_FAILURE);
	}
	ft_free_tab(res);
	return (EXIT_SUCCESS);
}
