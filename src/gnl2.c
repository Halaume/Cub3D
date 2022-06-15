/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:44:38 by ghanquer          #+#    #+#             */
/*   Updated: 2022/06/15 11:48:44 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_strlen(char *str)
{
	unsigned int	i;

	i = 0;
	if (str != NULL)
	{
		while (str[i])
			i++;
	}
	return (i);
}

int	check_line(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	else
	{
		while (str[i])
		{
			if (str[i] == '\n')
				return (0);
			i++;
		}
	}
	return (1);
}

int	fill_line(char *line, char *buffer, int j, int i)
{
	if (line)
	{
		while (line[++i])
		{
			buffer[j] = line[i];
			j++;
		}
	}
	return (j);
}
