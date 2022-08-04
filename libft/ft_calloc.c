/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:58:33 by nflan             #+#    #+#             */
/*   Updated: 2022/08/04 18:37:39 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*tab;

	tab = NULL;
	tab = malloc(nmemb * size);
	if (!tab)
		return (NULL);
	ft_bzero(tab, nmemb * size);
	return (tab);
}

void	ft_bspace(void *s, size_t n)
{
	unsigned char	*str;
	size_t			i;

	str = s;
	i = 0;
	if (n > 0)
	{
		while (i < n)
			str[i++] = ' ';
		str[n - 1] = '\0';
	}
	s = str;
}

void	*ft_calmap(size_t nmemb, size_t size)
{
	void	*tab;

	tab = NULL;
	tab = malloc(nmemb * size);
	if (!tab)
		return (NULL);
	ft_bspace(tab, nmemb * size);
	return (tab);
}
