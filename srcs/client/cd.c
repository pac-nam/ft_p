#include "client.h"

static int	ft_close_cd(int fd)
{
	if (fd > 0)
		close(fd);
	return (error_handling(451));
}

static int	change_to_home_or_old(t_context *ctx, char *new)
{
	char	*new_dir;
	t_stat	st;
	int		fd;

	if (!(new_dir = ft_getenv(new, ctx->env)))
	{
		ft_dprintf(2, "%s doesn't exist\n", new_dir);
		return (2);
	}
	if ((fd = open(new_dir, O_RDONLY)) == -1)
		return (ft_close_cd(-1));
	if (fstat(fd, &st) == -1)
		return (ft_close_cd(fd));
	close(fd);
	if (!S_ISDIR(st.st_mode))
		return (error_handling(451));
	if (chdir(new_dir) == -1)
		return (error_handling(451));
	if (ft_setnewpwd(new_dir, ctx->env))
		return (error_handling(451));
	return (error_handling(212));
}

static int	change_dir(t_context *ctx, char *new)
{
	t_stat	st;
	int		fd;

	if ((fd = open(new, O_RDONLY)) == -1)
		return (ft_close_cd(-1));
	if (fstat(fd, &st) == -1)
		return (ft_close_cd(fd));
	close(fd);
	if (!S_ISDIR(st.st_mode))
		return (error_handling(451));
	if (chdir(new) == -1)
		return (error_handling(451));
	if (ft_setnewpwd(new, ctx->env))
		return (error_handling(451));
	return (error_handling(212));
}

static int	change_directory(char **cmd, t_context *ctx)
{
	if (ft_tablen(cmd) == 1 || !ft_strcmp(cmd[1], "~"))
		return (change_to_home_or_old(ctx, "HOME"));
	else if (!ft_strcmp(cmd[1], "-"))
		return (change_to_home_or_old(ctx, "OLDPWD"));
	else
		return (change_dir(ctx, cmd[1]));
	return (error_handling(212));
}

int			builtin_cd(char **cmd, t_context *ctx)
{
	if (ft_tablen(cmd) > 2)
		return (error_handling(501));
	return (change_directory(cmd, ctx));
}
