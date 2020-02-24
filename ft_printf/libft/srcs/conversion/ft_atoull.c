/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoull.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomasbleuse <thomasbleuse@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 09:43:25 by tbleuse           #+#    #+#             */
/*   Updated: 2019/12/16 10:25:45 by thomasbleus      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	ft_atoull take a string in parameter and convert it to unsigned long long.
**	If in the string there is a non digit charactere, ft_atoull will stop.
**	Be careful, ft_atoull can overflow.
*/

unsigned long long			ft_atoull(const char *str)
{
	unsigned long long		nb;
	int						i;

	nb = 0;
	i = 0;
	while (str[i] == '\r' || str[i] == '\v' || str[i] == '\t'
			|| str[i] == '\f' || str[i] == '\n' || str[i] == ' ')
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] > 47 && str[i] < 58)
	{
		nb = nb * 10;
		nb = nb + ((int)str[i] - '0');
		i++;
	}
	return (nb);
}
