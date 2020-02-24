#include "client.h"

int				send_login(t_context *ctx, char *ip, short port)
{
	char		*user;
	t_sockaddr	adr;

	adr.sin_family = AF_INET;
	adr.sin_port = htons(port);
	adr.sin_addr.s_addr = inet_addr(ip);
	if (!(user = ft_strjoin(ctx->login, ":")))
		return (EXIT_FAILURE);
	if (!(user = ft_strjoinfree(user, ctx->pass, 3)))
		return (EXIT_FAILURE);
	if (connect(ctx->socket, (struct sockaddr *)&adr, sizeof(adr)) == -1)
	{
		error_handling(425);
		ft_strdel(&user);
		return (EXIT_FAILURE);
	}
	error_handling(225);
	if (send(ctx->socket, user, ft_strlen(user), 0) == -1)
		ft_dprintf(2, "Failed to send\n");
	ft_strdel(&user);
	return (EXIT_SUCCESS);
}

int				handle_login(t_context *ctx, char *ip, short port)
{
	error_handling(332);
	error_handling(531);
	error_handling(532);
	while (!(ctx->login = get_login()))
		;
	error_handling(331);
	while (!(ctx->pass = get_password()))
		;
	if (send_login(ctx, ip, port))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
