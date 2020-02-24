#include "client.h"

static int	error_handling2(int code)
{
	if (code == 331)
		ft_printf("[%d] %s\n", code, USER_OK_NOW_PASS);
	else if (code == 425)
		ft_printf("[%d] Can't open data connection.\n", code);
	else if (code == 451)
		ft_printf("[%d] %s\n", code, REQUEST_ABORT);
	else if (code == 500)
		ft_printf("[%d] Command unrecognized\n", code);
	else if (code == 501)
		ft_printf("[%d] Syntax error in parameters or arguments.\n", code);
	else if (code == 502)
		ft_printf("[%d] Command not implemented.\n", code);
	else if (code == 530)
		ft_printf("[%d] Not logged in.\n", code);
	else if (code == 532)
		ft_printf("[%d] Need account for storing files.\n", code);
	else if (code == 550)
		ft_printf("[%d] %s\n", code, FILE_UNVAILABLE);
	else if (code == 552)
		ft_printf("[%d] %s directory or dataset).\n", code, EXCEEDED_ALLOC);
	return (code);
}

int			error_handling(int code)
{
	if (code == 200)
		ft_printf("[%d] %s\n", code, CMD_SUCCESS);
	else if (code == 202)
		ft_printf("[%d] %s\n", code, CMD_NOT_IMPL);
	else if (code == 211)
		ft_printf("[%d] System status, or system help reply.\n", code);
	else if (code == 212)
		ft_printf("[%d] Directory status.\n", code);
	else if (code == 214)
		ft_printf("[%d] Help message.\n", code);
	else if (code == 230)
		ft_printf("[%d] %s\n", code, USER_LOGGED);
	else if (code == 226)
		ft_printf("[%d] Closing data connection.\n", code);
	else if (code == 225)
		ft_printf("[%d] %s\n", code, CONNECT_OPEN);
	else if (code == 332)
		ft_printf("[%d] %s\n", code, NEED_ACCOUNT);
	else
		return (error_handling2(code));
	return (code);
}
