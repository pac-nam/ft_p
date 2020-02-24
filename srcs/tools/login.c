#include "ft_p.h"

static int		hide_stdin(t_termios *save)
{
	struct termios	term;
	if (tcgetattr(STDIN_FILENO, save) == -1)
		return (1);
	term = *save;
	term.c_lflag &= ~(ECHO);
	term.c_cc[VSTOP] = 0;
	term.c_cc[VSTART] = 0;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &term) == -1)
		return (1);
	return (0);
}

static int		show_stdin(t_termios *save)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, save) == -1)
		return (1);
	return (0);
}

char		*get_login(void)
{
	int		len;
	char	buf[256];

	write(1, "login: ", 7);
	len = read(STDIN_FILENO, buf, 256);
	if (len > 210 || len <= 1)
	{
		ft_dprintf(2, "\n%sERROR: %s%s", RED, BAD_LOGIN, RESET);
		return (NULL);
	}
	buf[len - 1] = '\0';
	if (ft_strchr(buf, ':') || ft_strchr(buf, '\n'))
	{
		ft_dprintf(2, "%s%s%s", RED, BAD_LCHAR, RESET);
		return (NULL);
	}
	return (ft_strdup(buf));
}

char		*get_password(void)
{
	int				len;
	t_termios		tmp;
	char			buf[256];

	write(1, "password: ", 11);
	if (hide_stdin(&tmp))
		return (NULL);
	len = read(STDIN_FILENO, buf, 256);
	if (len > 210 || len <= 1)
	{
		ft_dprintf(2, "\n%sERROR: %s%s", RED, BAD_PASS, RESET);
		if (show_stdin(&tmp))
			exit(1);
		return (NULL);
	}
	if (show_stdin(&tmp))
		exit(1);
	buf[len - 1] = '\0';
	if (ft_strchr(buf, ':') || ft_strchr(buf, '\n'))
	{
		ft_dprintf(2, "\n%s%s%s\n", RED, BAD_PCHAR, RESET);
		return (NULL);
	}
	printf("\n");
	return (sha512(buf));
}
