/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnoufel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 10:29:20 by bnoufel           #+#    #+#             */
/*   Updated: 2019/10/07 10:29:24 by bnoufel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

static void		reset_struct(t_core *core, int fd)
{
	core->padding = 0;
	core->precision = 0;
	core->fd = fd;
	core->flags = 0;
	core->modifier = 0;
	core->type = 0;
	core->star_preci = 0;
	core->star_padd = 0;
	core->prefix[0] = '\0';
}

int				print_buffer(t_core *core)
{
	if ((core->type_printf & is_printf) || (core->type_printf & is_dprintf))
		write(core->fd, core->buffer, core->index);
	else if ((core->type_printf & is_asprintf)
		|| core->type_printf & is_sprintf
		|| core->type_printf & is_snprintf)
	{
		if (!(*(core->ret_asprintf) = 
		ft_strjoinfree(*(core->ret_asprintf), core->buffer, 1)))
			return (0);
	}
	else if (core->type_printf & is_fprintf)
		fwrite(core->buffer, sizeof(char), core->index, core->stream);
	return (1);
}

int				ft_core(t_core *core, const char *str, int fd, va_list ap)
{
	int			i;

	i = 0;
	while (str[i] && core->count != -2)
	{
		reset_struct(core, fd);
		if (str[i] != '%')
			ft_reset_buffer(core, 1, str[i++], NULL);
		else
		{
			ft_flag(str, &i, core);
			ft_convert(core, ap);
		}
	}
	if (core->count != -2)
		return (print_buffer(core));
	return (1);
}