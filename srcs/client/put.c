#include "client.h"

static int		check_and_send2(char *str, t_context *ctx, char **cmd)
{
	char		check[512];

	ft_bzero(check, 512);
	if ((ft_asprintf(&str, "%s", cmd[1])) == -1)
		return (error_handling(552));
	if (send(ctx->socket, str, ft_strlen(str), 0) == -1)
		return (error_handling(451));
	ft_strdel(&str);
	if ((recv(ctx->socket, check, 512, 0)) == -1)
		return (error_handling(451));
	if (!(ft_strcmp(check, ACCEPT)))
		return (200);
	return (error_handling(451));
}

static int		check_and_send(t_context *ctx, char **cmd, t_stat *st)
{
	char		*str;
	char		check[512];

	ft_bzero(check, 512);
	if ((ft_asprintf(&str, "%s %d %d", cmd[0],
		ft_strlen(cmd[1]), st->st_size)) == -1)
		return (error_handling(552));
	if (send(ctx->socket, str, ft_strlen(str), 0) == -1)
		return (error_handling(451));
	if ((recv(ctx->socket, check, 512, 0)) == -1)
		return (error_handling(451));
	ft_strdel(&str);
	if (!(ft_strcmp(check, ACCEPT)))
		return (check_and_send2(str, ctx, cmd));
	return (error_handling(451));
}

static int		send_file(t_context *ctx, char **cmd, int fd, t_stat *st)
{
	if (fstat(fd, st) < 0)
	{
		close(fd);
		if (errno == EEXIST)
			return (error_handling(550));
		return (EXIT_FAILURE);
	}
	if (S_ISDIR(st->st_mode))
		return (error_handling(451));
	if (!(st->st_mode & S_IRUSR) || !(st->st_mode & S_IRGRP))
		return (error_handling(451));
	return (check_and_send(ctx, cmd, st));
}

static size_t	read_file(char **cmd, t_context *ctx, int fd)
{
	t_stat		st;
	char		check[512];
	int			res;
	char		buf[MAX_SEND];

	ft_bzero(check, 512);
	if ((res = send_file(ctx, cmd, fd, &st)) != 200)
		return (res);
	while ((res = read(fd, buf, MAX_SEND)) > 0)
	{
		buf[res] = '\0';
		if (send(ctx->socket, buf, res, 0) == -1)
			return (error_handling(451));
		if ((recv(ctx->socket, check, 512, 0)) == -1)
			return (error_handling(451));
		if (!(ft_strcmp(check, REFUSE)))
			return (error_handling(500));
	}
	return (error_handling(200));
}

int				send_put(char **cmd, t_context *ctx)
{
	int			fd;
	int			ret;

	if (ft_tablen(cmd) != 2)
		return (error_handling(501));
	if ((fd = open(cmd[1], O_RDONLY)) == -1)
		return (error_handling(550));
	ret = (read_file(cmd, ctx, fd));
	close(fd);
	return (ret);
}
