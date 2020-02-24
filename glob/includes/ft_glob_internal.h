#ifndef __FT_GLOB_INTERNAL_H
# define __FT_GLOB_INTERNAL_H

# include "ft_glob.h"
# include <dirent.h>
# include <unistd.h>

typedef struct dirent		t_dirent;

typedef struct				s_data_glob
{
	char					*pattern;
	struct s_data_glob		*head;
	struct s_data_glob		*next;
}							t_data_glob;

typedef struct				s_parse_glob
{
	char					*before;
	char					*middle;
	char					*after;
}							t_parse_glob;

int							save_res_glob(t_data_glob **glob, char *pattern);
size_t						lst_data_glob_size(t_data_glob *data);
void						free_glob_lst(t_data_glob **glob);
int							split_pattern_star(char *pattern, t_parse_glob *g);
int							start_glob(char *cmd, char *patt, t_data_glob **d);
#endif
