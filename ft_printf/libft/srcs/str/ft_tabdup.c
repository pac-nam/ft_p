#include <stdlib.h>
#include "str.h"

/*
**	ft_strdup duplicate the tab s1.
**	If src and dst are close, use ft_memmove to avoid overlap.
**	WARNING: ft_strdup use malloc. So it need to be free to avoid leaks.
**	WARNING: malloc can fail in this case, NULL is returned.
*/

char				**ft_tabdup(char **s1)
{
	char			**tab;
	const size_t	len = ft_tablen(s1);
	size_t			i;

	i = 0;
	if (!(tab = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	while (i < len)
	{
		if (!(tab[i] = ft_strdup(s1[i])))
			return (NULL);
		i++;
	}
	tab[i] = 0;
	return (tab);
}
