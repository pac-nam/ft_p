#include "server.h"

void		showuser(t_user *list)
{
	t_user		*tmp;

	tmp = list;
	if (!tmp)
		printf("no users registered\n");
	while (tmp)
	{
		printf("[%s%s%s][%s%s%s]\n",
		BLUE, tmp->login, RESET, RED, tmp->password, RESET);
		tmp = tmp->next;
	}
}
