/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomasbleuse <thomasbleuse@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 14:03:55 by tbleuse           #+#    #+#             */
/*   Updated: 2019/12/02 12:56:54 by thomasbleus      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_free_tab(char **tab)
{
	int		i;

	if (tab)
	{
		i = 0;
		while (tab[i])
			free(tab[i++]);
		free(tab);
		tab = NULL;
	}
}