/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 15:09:50 by nflan             #+#    #+#             */
/*   Updated: 2022/08/02 15:20:33 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str)
		while (str[i])
			i++;
	return (i);
}

size_t	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (0);
	if (tab[i])
		while (tab[i])
			i++;
	return (i);
}
