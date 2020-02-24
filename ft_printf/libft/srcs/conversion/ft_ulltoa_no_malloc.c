/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa_no_malloc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomasbleuse <thomasbleuse@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 10:04:25 by tbleuse           #+#    #+#             */
/*   Updated: 2020/01/11 13:59:06 by thomasbleus      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "str.h"
#include "conversion.h"

/*
**	ft_ulltoa_no_malloc convert the value passed in parameter to string in base
**	10 and put it in the dst passed in parameter.
**	WARNING: dst need sufficient space.
*/

char			*ft_ulltoa_no_malloc(char *dst, unsigned long long n)
{
	int						i;
	unsigned long long		n2;

	i = 0;
	n2 = n;
	if (n == 0)
		return (ft_strcpy(dst, "0"));
	while (n2 > 0)
	{
		n2 = n2 / 10;
		i++;
	}
	dst[i--] = '\0';
	while (n != 0)
	{
		dst[i--] = HEXA[(n % 10)];
		n = n / 10;
	}
	return (dst);
}
