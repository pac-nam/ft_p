#include "server.h"

t_user	*search_user(t_user *list, char *login)
{
	t_user		*tmp;

	tmp = list;
	while (tmp)
	{
		if (!ft_strcmp(tmp->login, login))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	newuser_second(t_context *ctx, char *login)
{
	char		*pass1;
	char		*pass2;

	if (!(pass1 = get_password()))
		return ;
	write(1, "confirm ", 8);
	if (!(pass2 = get_password()))
	{
		free(pass1);
		return ;
	}
	if (ft_strncmp(pass1, pass2, 256))
	{
		free(pass1);
		free(pass2);
		ft_dprintf(2, "ERROR: different passwords\n");
		return ;
	}
	if (!add_in_pass_file(login, pass1, ctx->pass_file, &(ctx->user_list)))
		ft_printf("%s succesfully added\n", login);
	else
		ft_dprintf(2, "%s can not be added to %s\n", login, ctx->pass_file);
}

void	newuser(t_context *ctx)
{
	char		*login;

	while (1)
	{
		if (!(login = get_login()))
			return ;
		if (search_user(ctx->user_list, login))
		{
			free(login);
			ft_dprintf(2, "login already used\n");
			continue ;
		}
		break ;
	}
	newuser_second(ctx, login);
	free(login);
}

void	deleteuser(t_context *ctx)
{
	char		*login;
	char		*pass;

	if (!(login = get_login()))
		return ;
	if (!(pass = get_password()))
	{
		free(login);
		return ;
	}
	if (!(remove_from_pass_file(login, pass, ctx->pass_file,
			&(ctx->user_list))))
		ft_printf("%s succesfully deleted\n", login);
	else
		ft_dprintf(2, "%s can not be deleted from %s", login, ctx->pass_file);
	free(login);
	free(pass);
}
