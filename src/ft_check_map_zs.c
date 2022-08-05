/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_zs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 12:12:42 by nflan             #+#    #+#             */
/*   Updated: 2022/08/05 12:12:52 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_check_space(char **map, int y, int x)
{
	if (y - 1 >= 0)
		if (map[y - 1][x] != ' ' && map[y - 1][x] != '1')
			return (1);
	if (y + 1 < (int)ft_tablen(map))
		if (map[y + 1][x] != ' ' && map[y + 1][x] != '1')
			return (1);
	if (x - 1 >= 0)
		if (map[y][x - 1] != ' ' && map[y][x - 1] != '1')
			return (1);
	if (x + 1 < (int)ft_strlen(map[0]))
		if (map[y][x + 1] != ' ' && map[y][x + 1] != '1')
			return (1);
	return (0);
}

int	ft_spaces(char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == ' ')
			{
				if (ft_check_space(map, y, x))
					return (ft_poserr(y, x, "Carte invalide (caractere \
invalide autour d'un ' '): "));
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	ft_check_zerobis(char **map, int y, int x)
{
	if (x - 1 >= 0)
		if (map[y][x - 1] == ' ')
			return (1);
	if (map[y][x] == ' ')
		return (1);
	if (x + 1 < (int)ft_strlen(map[0]))
		if (map[y][x + 1] == ' ')
			return (1);
	return (0);
}

int	ft_check_zero(char **map, int y, int x)
{
	if (y - 1 >= 0)
		if (ft_check_zerobis(map, y - 1, x))
			return (1);
	if (y + 1 < (int)ft_tablen(map))
		if (ft_check_zerobis(map, y + 1, x))
			return (1);
	if (x - 1 >= 0)
		if (map[y][x - 1] == ' ')
			return (1);
	if (x + 1 < (int)ft_strlen(map[0]))
		if (map[y][x + 1] == ' ')
			return (1);
	return (0);
}

int	ft_zero(char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '0')
			{
				if (ft_check_zero(map, y, x))
					return (ft_poserr(y, x, "Carte invalide (caractere invalide\
 autour d'un '0'): "));
			}
			x++;
		}
		y++;
	}
	return (0);
}
