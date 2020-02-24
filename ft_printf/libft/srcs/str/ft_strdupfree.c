/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbleuse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 11:49:49 by tbleuse           #+#    #+#             */
/*   Updated: 2018/11/09 12:51:43 by tbleuse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "str.h"

/*
**	ft_strdup duplicate the string s1 and free tofree.
**	If src and dst are close, use ft_memmove to avoid overlap.
**	WARNING: ft_strdup use malloc. So it need to be free to avoid leaks.
**	WARNING: malloc can fail in this case, NULL is returned.
*/

char	*ft_strdupfree(const char *s1, char **tofree)
{
	char	*str;

	if (!(str = (char *)malloc(ft_strlen(s1) + 1)))
	{
		ft_strdel(tofree);
		return (NULL);
	}
	ft_strdel(tofree);
	return (ft_strcpy(str, s1));
}
