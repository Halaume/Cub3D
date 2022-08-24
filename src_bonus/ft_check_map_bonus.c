/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:51:30 by nflan             #+#    #+#             */
/*   Updated: 2022/08/24 11:20:24 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

int	ft_charcheck(char **map, int y, int x)
{
	static int	nb = 0;

	if (ft_valid_elems(map[y][x]))
		return (ft_poserr(y, x, "Carte invalide (caractere invalide): "));
	else if (map[y][x] == 'W' || map[y][x] == 'N' || map[y][x] == 'S'
		|| map[y][x] == 'E')
	{
		if (ft_check_zero(map, y, x))
			return (ft_poserr(y, x, "Carte invalide (caractere invalide autour \
du joueur): "));
		nb++;
	}
	else if (map[y][x] == '0')
	{
		if (ft_check_zero(map, y, x))
			return (ft_poserr(y, x, "Carte invalide (caractere invalide autour \
d'un '0'): "));
	}
	if (nb > 1)
		return (ft_putstr_error("Error\nTrop de joueurs sur la carte\n"));
	return (0);
}

int	ft_parsingage(char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (ft_charcheck(map, y, x))
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

int	ft_valid_map(t_info *info)
{
	if (!info->map)
		return (ft_putstr_error("Error\nMap error\n"));
	if (ft_sides(info->map) || ft_parsingage(info->map))
		return (1);
	if (ft_doors(info, 1))
		return (1);
	if (ft_doors(info, 2))
		return (1);
	return (0);
}
