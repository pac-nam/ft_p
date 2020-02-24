#include "ft_glob_internal.h"

static int	find_star(char *pattern)
{
	int		i;

	i = 0;
	while (pattern[i])
	{
		if (pattern[i] == '*')
			return (i);
		i++;
	}
	return (0);
}

static int	split_before_star(char *pattern, t_parse_glob **glob)
{
	int		i;

	i = find_star(pattern);
	while (pattern[i] && pattern[i] != '/')
		i--;
	if (i < 0)
	{
		if (!((*glob)->before = ft_strdup("")))
			return (EXIT_FAILURE);
	}
	else
	{
		if (!((*glob)->before = ft_strndup(pattern, i + 1)))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	split_middle_star(char *pattern, t_parse_glob **glob)
{
	int		i;
	int		start;
	int		end;

	end = 0;
	i = find_star(pattern);
	while (pattern[i] && pattern[i] != '/')
		i--;
	start = i;
	if (i < 0)
		i = 0;
	while (pattern[++start] && pattern[start] != '/')
		end++;
	if (pattern[i] == '/')
		i++;
	if (!((*glob)->middle = ft_strsub(pattern, i, end)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	split_after_star(char *pattern, t_parse_glob **glob)
{
	int		i;
	int		j;

	j = ft_strlen(pattern);
	i = find_star(pattern);
	while (pattern[i] && pattern[i] != '/')
		i++;
	if (!((*glob)->after = ft_strsub(pattern, i, j - i)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int			split_pattern_star(char *pattern, t_parse_glob *glob)
{
	if (split_before_star(pattern, &glob))
		return (EXIT_FAILURE);
	if (split_middle_star(pattern, &glob))
		return (EXIT_FAILURE);
	if (split_after_star(pattern, &glob))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
