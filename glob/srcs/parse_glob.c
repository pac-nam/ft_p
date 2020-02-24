#include "ft_glob_internal.h"

static int			match(char *s1, char *s2)
{
	if (*s1 == '\0' && *s2 == '\0')
		return (1);
	else if (*s1 == '\0' && *s2 != '*')
		return (0);
	else if (*s1 == *s2)
		return (match(s1 + 1, s2 + 1));
	else if (*s2 == '*' && *s1)
		return (match(s1 + 1, s2) || match(s1 + 1, s2 + 1));
	else if (*s2 == '*' && !(*s1))
		return (match(s1, s2 + 1));
	else
		return (0);
}

static int			free_parse_glob(t_parse_glob *glob, int ret)
{
	ft_strdel(&(glob->before));
	ft_strdel(&(glob->middle));
	ft_strdel(&(glob->after));
	return (ret);
}

static int			check_access_glob_file(t_parse_glob *glob, char *d_name)
{
	char			*str;

	ft_asprintf(&str, "%s%s%s", glob->before, d_name, glob->after);
	if (access(str, F_OK) == -1)
	{
		ft_strdel(&str);
		ft_dprintf(2, "No match found\n");
		return (EXIT_FAILURE);
	}
	ft_strdel(&str);
	return (EXIT_SUCCESS);
}

int					match_glob(t_dirent *rdir, t_parse_glob glob,
								t_data_glob **data, char *cmd)
{
	char			*str;

	if (!ft_strcmp(rdir->d_name, ".") || !ft_strcmp(rdir->d_name, "..")
	|| rdir->d_name[0] != '.')
		return (EXIT_FAILURE);
	if (!check_access_glob_file(&glob, rdir->d_name))
	{
		ft_asprintf(&str, "%s %s%s%s", cmd, glob.before,
					rdir->d_name, glob.after);
		save_res_glob(data, str);
		ft_strdel(&str);
	}
	return (EXIT_SUCCESS);
}

int					start_glob(char *cmd, char *pattern, t_data_glob **data)
{
	t_parse_glob	glob;
	DIR				*odir;
	t_dirent		*rdir;

	if (split_pattern_star(pattern, &glob))
		return (EXIT_FAILURE);
	if (!(odir = opendir(ft_strlen(glob.before) > 0 ? glob.before : ".")))
		return (free_parse_glob(&glob, 1));
	while ((rdir = readdir(odir)))
	{
		if (match(rdir->d_name, glob.middle)
			|| !ft_strncmp(rdir->d_name, glob.middle, 2))
		{
			if (match_glob(rdir, glob, data, cmd))
				continue ;
		}
	}
	closedir(odir);
	return (free_parse_glob(&glob, 0));
}
