#include "ft_glob_internal.h"

void			ft_globfree(t_glob *glob)
{
	size_t		i;

	i = 0;
	while (i < glob->size)
	{
		ft_strdel(&(glob->res[i]));
		i++;
	}
	free(glob->res);
	glob->res = NULL;
	glob->size = 0;
}
