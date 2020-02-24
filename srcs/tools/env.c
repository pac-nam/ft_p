#include "ft_p.h"

static int	save_env(t_env **ctx, char *name, char *value)
{
	if (!*ctx)
	{
		if (!((*ctx) = (t_env *)malloc(sizeof(t_env))))
			return (EXIT_FAILURE);
		if (!((*ctx)->name = ft_strdup(name)))
			return (EXIT_FAILURE);
		if (!((*ctx)->value = ft_strdup(value)))
			return (EXIT_FAILURE);
		(*ctx)->head = *ctx;
		(*ctx)->next = NULL;
	}
	else
	{
		if (!((*ctx)->next = (t_env *)malloc(sizeof(t_env))))
			return (EXIT_FAILURE);
		if (!((*ctx)->next->name = ft_strdup(name)))
			return (EXIT_FAILURE);
		if (!((*ctx)->next->value = ft_strdup(value)))
			return (EXIT_FAILURE);
		(*ctx)->next->head = (*ctx)->head;
		(*ctx)->next->next = NULL;
		(*ctx) = (*ctx)->next;
	}
	return (EXIT_SUCCESS);	
}

int			set_env(t_env **ctx, char **env)
{
	size_t	i;
	size_t	len;
	char	**tab;

	i = 0;
	len = ft_tablen(env);
	if (!len)
		return (EXIT_FAILURE);
	while (i < len)
	{
		if (!(tab = ft_strsplit(env[i], '=')))
			return (EXIT_FAILURE);
		if (ft_tablen(tab) != 2)
		{
			i++;
			continue ;
		}
		if (save_env(ctx, tab[0], tab[1]))
			return (EXIT_FAILURE);
		ft_free_tab(tab);
		i++;
	}
	return (EXIT_SUCCESS);
}

char		*ft_getenv(char *search, t_env *env)
{
	t_env	*tmp;

	tmp = env->head;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, search))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int			ft_setnewpwd(char *newpwd, t_env *env)
{
	char	*pwd;
	char	*tmp;

	if (!(pwd = ft_getenv("PWD", env)))
		return (EXIT_FAILURE);
	env = env->head;
	while (env)
	{
		if (!ft_strcmp("OLDPWD", env->name))
		{
			tmp = env->value;
			if (!(env->value = ft_strdup(pwd)))
				return (EXIT_FAILURE);
			ft_strdel(&(tmp));
		}
		if (!ft_strcmp("PWD", env->name))
		{
			tmp = env->value;
			if (!(env->value = ft_strdup(newpwd)))
				return (EXIT_FAILURE);
			ft_strdel(&(tmp));
		}
		env = env->next;
	}
	return (EXIT_SUCCESS);
}

void		free_env(t_env **env)
{
	t_env	*head;
	t_env	*tmp;

	head = (*env)->head;
	while (head)
	{
		tmp = head;
		head = head->next;
		ft_strdel(&(tmp->name));
		ft_strdel(&(tmp->value));
		ft_memdel((void *)&(tmp));
	}
}
