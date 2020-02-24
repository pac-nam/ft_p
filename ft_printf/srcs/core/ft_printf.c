/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 10:29:37 by bnoufel           #+#    #+#             */
/*   Updated: 2019/10/07 10:29:38 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

int				ft_printf(const char *str, ...)
{
	t_core		core;
	int			fd;
	va_list		ap;

	if (!str)
		return (-1);
	fd = 1;
	ft_init_struct(&core, fd);
	core.ret_asprintf = NULL;
	core.type_printf |= is_printf;
	va_start(ap, str);
	if (!(ft_core(&core, str, fd, ap)))
		return (-1);
	va_end(ap);
	if (core.count == -2)
		return (-1);
	return (core.count);
}

int				ft_dprintf(int fd, const char *str, ...)
{
	t_core		core;
	va_list		ap;

	if (!str)
		return (-1);
	ft_init_struct(&core, fd);
	core.type_printf |= is_dprintf;
	va_start(ap, str);
	if (!(ft_core(&core, str, fd, ap)))
		return (-1);
	va_end(ap);
	if (core.count == -2)
		return (-1);
	return (core.count);
}

int			ft_asprintf(char **ret, const char *str, ...)
{
	t_core		core;
	va_list		ap;

	if (!str)
		return (-1);
	if (!((*ret) = ft_strnew(1)))
		return (-1);
	ft_init_struct(&core, 1);
	core.ret_asprintf = ret;
	core.type_printf |= is_asprintf;
	va_start(ap, str);
	if (!(ft_core(&core, str, 1, ap)))
		return (-1);
	va_end(ap);
	if (core.count == -2)
		return (-1);
	return (core.count);
}

int			ft_sprintf(char *ret, const char *str, ...)
{
	t_core		core;
	va_list		ap;
	char		*ptr;

	if (!str)
		return (-1);
	if (!(ptr = ft_strnew(1)))
		return (-1);
	ft_init_struct(&core, 1);
	core.ret_asprintf = &ptr;
	core.type_printf |= is_sprintf;
	va_start(ap, str);
	if (!(ft_core(&core, str, 1, ap)))
		return (-1);
	va_end(ap);
	ft_strcpy(ret, *(core.ret_asprintf));
	ft_strdel(core.ret_asprintf);
	if (core.count == -2)
		return (-1);
	return (core.count);
}

int			ft_snprintf(char *ret, size_t size, const char *str, ...)
{
	t_core		core;
	va_list		ap;
	char		*ptr;
	size_t		len;

	if (!str)
		return (-1);
	if (!(ptr = ft_strnew(1)))
		return (-1);
	ft_init_struct(&core, 1);
	core.ret_asprintf = &ptr;
	core.type_printf |= is_snprintf;
	va_start(ap, str);
	if (!(ft_core(&core, str, 1, ap)))
		return (-1);
	va_end(ap);
	if (!core.len)
		core.len = core.index;
	len = (core.len < size) ? core.len : size;
	ft_strncpy(ret, *(core.ret_asprintf), len);
	ft_strdel(core.ret_asprintf);
	if (core.count == -2)
		return (-1);
	return (core.count);
}
