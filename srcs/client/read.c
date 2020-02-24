#include "client.h"

static void	sig_h(int sig)
{
	sig = 10;
	ft_putendl("");
	print_prompt();
}

static int	read_prompt(t_context **ctx)
{
	int		ret;
	char	buf[LINE_MAX];

	signal(SIGINT, sig_h);
	while ((ret = read(STDIN_FILENO, buf, LINE_MAX)) > 0)
	{
		if (ret > 1 && buf[ret - 1] == 10)
		{
			buf[ret - 1] = '\0';
			if (handle_cmd(buf, (*ctx)))
				return (EXIT_FAILURE);
		}
		print_prompt();
	}
	if (!ret)
		quit(1, (*ctx));
	return (EXIT_SUCCESS);
}

int			handle_client(t_context **ctx)
{
	char	str[512];
	ssize_t	len;

	if ((len = recv((*ctx)->socket, str, 512, 0)) == -1)
		return (error_handling(451));
	str[len] = '\0';
	if (!ft_strcmp(str, CONNECTION_ACCEPTED))
	{
		(*ctx)->auth = true;
		if (!(g_login = ft_strdup((*ctx)->login)))
			return (error_handling(552));
		error_handling(230);
		print_prompt();
		return (read_prompt(ctx));
	}
	ft_dprintf(2, "\n%sUser or password are wrong%s!\n", RED, RESET);
	return (quit(1, *ctx));
}
