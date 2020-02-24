#include "server.h"

static uint16_t	verif_port(char *str)
{
	int			i;
	uint16_t	nb;

	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
		{
			ft_dprintf(2, PORT_DIGIT_ERROR);
			return (0);
		}
	if (i >= 7 || (nb = ft_atoi(str)) > 65535)
	{
		ft_dprintf(2, PORT_ERROR);
		return (0);
	}
	return (nb);
}

int				open_server_fd(t_context *ctx)
{
	ctx->sockaddr_server.sin_port = htons(ctx->port);
	ctx->sockaddr_server.sin_family = AF_INET;
	ctx->sockaddr_server.sin_addr.s_addr = INADDR_ANY;
	ctx->sock_fd_server = socket(AF_INET, SOCK_STREAM, 0);
	if (ctx->sock_fd_server == -1)
	{
		ft_dprintf(2, SOCKET_ERROR);
		return (1);
	}
	if ((bind(ctx->sock_fd_server,
	(struct sockaddr *)&(ctx->sockaddr_server),
	sizeof(t_sockaddr))) == -1)
	{
		ft_dprintf(2, BIND_ERROR);
		return (1);
	}
	if (listen(ctx->sock_fd_server, BACKLOG) == -1)
	{
		ft_dprintf(2, LISTEN_ERROR);
		return (1);
	}
	return (0);
}

static void		print_init_info(t_context *ctx)
{
	uint32_t		address;

	address = 0;
	printf("address: %d.%d.%d.%d\nport: %hu\n",
		address & 0xff,
		(address >> 8) & 0xff,
		(address >> 16) & 0xff,
		(address >> 24) & 0xff,
		ctx->port);
}

int				create_root(t_context *ctx)
{
	char	*tmp;

	if (mkdir(SERVER_FOLDER, 0755) && errno != EEXIST)
		return (ft_dprintf(2, "ERR: can't create %s\n", SERVER_FOLDER) && 0);
	if (chdir(SERVER_FOLDER))
		return (ft_dprintf(2, "ERR: can't move to %s\n", SERVER_FOLDER) && 0);
	if (!(ctx->root = getcwd(NULL, 0)))
		return (ft_dprintf(2, "ERR: getcwd fail\n") && 0);
	if (!(tmp = ft_strjoin("/", PASSWORDS)))
		return (ft_dprintf(2, "ERR: strjoin fail\n") && 0);
	if (!(ctx->pass_file = ft_strjoinfree(ctx->root, tmp, 2)))
		return (ft_dprintf(2, "ERR: strjoinfree fail\n") && 0);
	if (!(tmp = ft_strjoin("/", SERVER_LOGS)))
		return (ft_dprintf(2, "ERR: strjoin fail\n") && 0);
	if (!(ctx->log_folder = ft_strjoinfree(ctx->root, tmp, 2)))
		return (ft_dprintf(2, "ERR: strjoinfree fail\n") && 0);
	if (mkdir(ctx->log_folder, 0755) && errno != EEXIST)
		return (ft_dprintf(2, "ERR: can't create %s\n", ctx->log_folder) && 0);
	return (0);
}

int				init_struct(char *str, t_context *ctx)
{
	if (!(ctx->port = verif_port(str)))
		return (1);
	ctx->user_list = NULL;
	ctx->root = NULL;
	ctx->pass_file = NULL;
	ctx->log_folder = NULL;
	ctx->error = NULL;
	ctx->end = 0;
	if (create_root(ctx))
		return (1);
	print_init_info(ctx);
	return (open_server_fd(ctx));
}
