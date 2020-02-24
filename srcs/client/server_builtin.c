#include "client.h"

static int	construct_cmd(char **tab, char **str, int *len_arg_1)
{
	if (ft_tablen(tab) == 1)
	{
		if (ft_asprintf(str, ".") == -1)
			return (error_handling(552));
		*len_arg_1 = 1;
	}
	else
	{
		if (ft_asprintf(str, "%s", tab[1]) == -1)
			return (error_handling(552));
		*len_arg_1 = ft_strlen(tab[1]);
	}
	return (200);
}

static int	second_send(char *cmd, t_context *ctx)
{
	char	*content;
	char	tmp[512];
	ssize_t	len;

	ft_bzero(tmp, 512);
	if (send(ctx->socket, cmd, ft_strlen(cmd), 0) == -1)
		return (error_handling(451));
	if (recv(ctx->socket, tmp, 512, 0) == -1)
		return (error_handling(451));
	if (!(ft_strncmp(tmp, ACCEPT, ft_strlen(ACCEPT))))
	{
		len = ft_atoull(tmp + ft_strlen(ACCEPT) + 1);
		if (!(content = ft_strnew(len + 1)))
			return (error_handling(552));
		if (recv(ctx->socket, content, len, 0) == -1)
		{
			ft_strdel(&content);
			return (error_handling(451));
		}
		ft_printf("%s", content);
		ft_strdel(&content);
		return (200);
	}
	ft_strdel(&cmd);
	return (error_handling(451));
}

static int	first_send(char **tab, char *cmd, int len, t_context *ctx)
{
	char	*str;
	char	tmp[512];

	ft_bzero(tmp, 512);
	if (ft_asprintf(&str, "%s %d", tab[0], len) == -1)
		return (error_handling(552));
	if (send(ctx->socket, str, ft_strlen(str), 0) == -1)
	{
		ft_strdel(&str);
		return (error_handling(451));
	}
	ft_strdel(&str);
	if (recv(ctx->socket, tmp, 512, 0) == -1)
		return (error_handling(451));
	if (!(ft_strcmp(tmp, ACCEPT)))
		return (second_send(cmd, ctx));
	ft_strdel(&cmd);
	return (error_handling(451));
}

static int	send_pwd(char **tab, t_context *ctx)
{
	char		str[512];
	char		*f;

	ft_bzero(str, 512);
	if (ft_tablen(tab) != 1)
		return (error_handling(501));
	if (send(ctx->socket, tab[0], ft_strlen(tab[0]), 0) == -1)
		return (error_handling(451));
	if (recv(ctx->socket, str, 512, 0) == -1)
		return (error_handling(451));
	if (ft_strncmp(str, ACCEPT, ft_strlen(ACCEPT)) != 0)
		return (error_handling(451));
	if (send(ctx->socket, ACCEPT, ft_strlen(ACCEPT), 0) == -1)
		return (error_handling(451));
	if (!(f = ft_strnew(ft_atoull(str + ft_strlen(ACCEPT) + 1))))
		return (error_handling(552));
	if (recv(ctx->socket, f, ft_atoull(str + ft_strlen(ACCEPT) + 1), 0) == -1)
	{
		ft_strdel(&f);
		return (error_handling(451));
	}
	ft_printf("%s\n", f);
	ft_strdel(&f);
	return (error_handling(200));
}

int			server_builtin(char **tab, t_context *ctx)
{
	char	*str;
	int		res;
	int		len;

	if (!(ft_strcmp(tab[0], "pwd")))
		return (send_pwd(tab, ctx));
	if (!(ft_strcmp(tab[0], "mkdir")) && ft_tablen(tab) != 2)
		return (error_handling(501));
	else if (ft_tablen(tab) > 2)
		return (error_handling(501));
	if ((res = construct_cmd(tab, &str, &len)) != 200)
		return (res);
	if ((res = first_send(tab, str, len, ctx)) != 200)
		return (res);
	ft_strdel(&str);
	return (error_handling(200));
}
