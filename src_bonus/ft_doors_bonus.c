/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_doors_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 15:24:09 by nflan             #+#    #+#             */
/*   Updated: 2022/08/22 11:05:52 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//	TODO
//	Chain list -> pos x/y of door -> state Open/Close -> time last open
#include "../inc/cub3d.h"

int	ft_count_walldo(char **map, int y, int x, int *i)
{
	if (map[y - 1][x] == '1')
		(*i)++;
	if (map[y + 1][x] == '1')
		(*i)++;
	if (map[y][x - 1] == '1')
		(*i)++;
	if (map[y][x + 1] == '1')
		(*i)++;
	if (*i > 2)
		return (ft_poserr(y, x, "Carte invalide: trop de murs autour de\
 la porte en "));
	if (*i < 1)
		return (ft_poserr(y, x, "Carte invalide: pas assez de murs\
 autour de la porte en "));
	if (map[y - 1][x] == '1')
		if (map[y + 1][x] != '1')
			return (ft_poserr(y, x, "Carte invalide: les murs autour de\
 la porte ne sont pas en face en "));
	if (map[y][x - 1] == '1')
		if (map[y][x + 1] != '1')
			return (ft_poserr(y, x, "Carte invalide: les murs autour de\
 la porte ne sont pas en face en "));
	return (0);
}

int	ft_check_doors(char **map, int y, int x)
{
	int	i;

	//init i?

	if (ft_count_walldo(map, y, x, &i))
		return (1);
	if (ft_check_around(map, y - 1, x))
		return (1);
	if (ft_check_around(map, y + 1, x))
		return (1);
	if (map[y][x - 1] == ' ')
		return (1);
	if (map[y][x + 1] == ' ')
		return (1);
	return (0);
}

int	ft_doors(char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '2')
			{
				if (ft_check_doors(map, y, x))
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}
