#include "client.h"

int			send_mput(t_context *ctx, char *cmd)
{
	t_glob	glob;
	size_t	i;
	char	**tmp;

	i = 0;
	if (ft_glob(cmd, &glob))
		return (1);
	while (i < glob.size)
	{
		if (!(tmp = ft_strsplit(glob.res[i], ' ')))
		{
			ft_globfree(&glob);
			return (error_handling(552));
		}
		ft_strcpy(tmp[0], "put");
		send_put(tmp, ctx);
		ft_free_tab(tmp);
		i++;
	}
	ft_globfree(&glob);
	return (error_handling(200));
}
