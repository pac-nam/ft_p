#include "server.h"

void	ft_quit(t_process *process)
{
	send(process->sock_fd_client, "closing connection", 18, 0);
	return ;
}
