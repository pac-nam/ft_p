#include "client.h"

int			quit(int newline, t_context *ctx)
{
	if (newline)
		ft_putchar('\n');
	close(ctx->socket);
	ft_strdel(&g_login);
	return (error_handling(226));
}

int			send_builtin(char **tab)
{
	pid_t	pid;

	if ((pid = fork()) == -1)
	{
		ft_dprintf(2, "\nFork was failed\n");
		return (EXIT_FAILURE);
	}
	if (!ft_strcmp(tab[0], "lls"))
	{
		if (!(tab[0] = ft_strdupfree("/bin/ls", &(tab[0]))))
			return (EXIT_FAILURE);
	}
	else if (!(ft_strcmp(tab[0], "lpwd")))
	{
		if (!(tab[0] = ft_strdupfree("/bin/pwd", &(tab[0]))))
			return (EXIT_FAILURE);
	}
	if (pid > 0)
		wait4(0, NULL, 0, NULL);
	if (pid == 0)
		execv(tab[0], tab);
	return (EXIT_SUCCESS);
}
