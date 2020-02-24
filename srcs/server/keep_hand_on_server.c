#include "server.h"

static void		server_command_help(void)
{
	printf("-ping:        test the server\n");
	printf("-quit:        stop the server\n");
	printf("-newuser:     add user for connection\n");
	printf("-deleteuser:  delete an user\n");
	printf("-showuser:    print user list\n");
	printf("-help:        show the help\n");
}

static int		command_from_server(t_context *ctx)
{
	char	buf[512];
	int		len;

	write(1, "$ ", 2);
	while ((len = read(STDIN_FILENO, &buf, 512)) > 0)
	{
		buf[len - 1] = '\0';
		if (!ft_strcmp("ping", buf))
			printf("pong\n");
		else if (!ft_strcmp("newuser", buf))
			newuser(ctx);
		else if (!ft_strcmp("deleteuser", buf))
			deleteuser(ctx);
		else if (!ft_strcmp("showuser", buf))
			showuser(ctx->user_list);
		else if (!ft_strcmp("help", buf))
			server_command_help();
		else if (!ft_strcmp("quit", buf))
			break ;
		else
			ft_dprintf(2, "unknow command type \"help\" for help...\n");
		write(1, "$ ", 2);
	}
	ctx->end = 1;
	return (0);
}

int				keep_hand_on_server(t_context *ctx)
{
	int		process_id;

	if ((process_id = fork()) < 0)
	{
		ft_dprintf(2, "ERROR: fork fail\n");
		return (1);
	}
	if (process_id > 0)
		return (0);
	if (!(ctx->user_list = get_pass_file(ctx->pass_file)))
		return (1);
	command_from_server(ctx);
	ft_printf("server end\n");
	return (0);
}
