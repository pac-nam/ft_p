#include "client.h"

static int		client_connect(char *ip, short port, t_context *ctx)
{
	if (handle_login(ctx, ip, port))
		return (EXIT_FAILURE);
	if (handle_client(&ctx))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int		client(char **av, t_context *ctx)
{
	int			sock;
	int			port;
	char		*ip;

	ip = av[1];
	port = ft_atoi(av[2]);
	if (port > 65535 || !ft_strisdigit(av[2]))
	{
		ft_dprintf(2, PORT_ERROR);
		return (EXIT_FAILURE);
	}
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		ft_dprintf(2, SOCKET_ERROR);
		return (EXIT_FAILURE);
	}
	ctx->socket = sock;
	if (client_connect(ip, port, ctx))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int				main(int ac, char **av, char **env)
{
	t_context	ctx;

	if (ac != 3)
	{
		ft_dprintf(2, "usage: %s server port\n", av[0]);
		return (EXIT_FAILURE);
	}
	if (set_env(&(ctx.env), env))
		return (EXIT_FAILURE);
	ctx.auth = false;
	g_login = NULL;
	if (client(av, &ctx))
	{
		free_env(&(ctx.env));
		return (EXIT_FAILURE);
	}
	free_env(&(ctx.env));
	return (EXIT_SUCCESS);
}
