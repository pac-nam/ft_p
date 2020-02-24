#ifndef __FT_GLOB_H
# define __FT_GLOB_H
# include "ft_printf.h"

typedef struct		s_glob
{
	size_t			size;
	char			**res;
}					t_glob;

void				ft_globfree(t_glob *glob);
int					ft_glob(char *pattern, t_glob *glob);

#endif
