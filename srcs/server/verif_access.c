#include "server.h"

int			ret_free(void *ptr, int ret)
{
	free(ptr);
	return (ret);
}

size_t		index_last_slash(const char *str)
{
	size_t	last;

	last = ft_strlen(str);
	while (--last)
	{
		if (str[last] == '/' && str[last - 1] != '\\')
			return (last);
	}
	return (0);
}

int			verif_access(t_process *process, char *file)
{
	char	*new_path;

	new_path = NULL;
	if (!file || !process)
		return (1);
	if ((file[0] == '~' || file[0] == '/') && !(new_path = ft_strdup(file)))
		return (1);
	else if ((ft_asprintf(&new_path, "%s/%s", process->pwd, file)) == -1)
		return (1);
	new_path[index_last_slash(new_path) + 1] = '\0';
	if ((chdir(new_path) == -1))
		return (ret_free(new_path, 1));
	free(new_path);
	if (!(new_path = ft_strjoinfree(getcwd(NULL, 0), "/", 1)))
	{
		chdir(process->pwd);
		return (1);
	}
	chdir(process->pwd);
	if (ft_strncmp(process->root, new_path, ft_strlen(process->root)))
		return (ret_free(new_path, 1));
	free(new_path);
	return (0);
}

int			verif_dir_access(t_process *process, char *folder)
{
	char	*new_path;

	if (!folder || !process)
		return (1);
	if ((folder[0] == '~' || folder[0] == '/'))
	{
		if (!(new_path = ft_strdup(folder)))
			return (1);
	}
	else if ((ft_asprintf(&new_path, "%s/%s", process->pwd, folder)) == -1)
		return (1);
	if ((chdir(new_path) == -1))
		return (ret_free(new_path, 404));
	free(new_path);
	if (!(new_path = ft_strjoinfree(getcwd(NULL, 0), "/", 1)))
	{
		chdir(process->pwd);
		return (1);
	}
	chdir(process->pwd);
	if (ft_strncmp(process->root, new_path, ft_strlen(process->root)))
		return (ret_free(new_path, 403));
	free(new_path);
	return (0);
}
