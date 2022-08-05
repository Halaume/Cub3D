/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:51:30 by nflan             #+#    #+#             */
/*   Updated: 2022/08/05 12:15:13 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_valid_elems(char c)
{
	if (c != 'W' && c != 'N' && c != 'S' && c != 'E' && c != ' ' && c != '1'
		&& c != '0')
		return (1);
	return (0);
}

int	ft_elems(char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (ft_valid_elems(map[y][x]))
				return (ft_poserr(y, x, "Carte invalide (caractere invalide): \
"));
			x++;
		}
		y++;
	}
	return (0);
}

int	ft_checkside(char c)
{
	if (c != ' ' && c != '1')
		return (1);
	return (0);
}

int	ft_sides(char **map)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	while (map[y++] && y + 1 < (int)ft_tablen(map))
		if (ft_checkside(map[y][x]))
			return (ft_poserr(y, x, "Carte invalide (ni ' ' ni '1') sur les \
contours de la carte: "));
	while (map[y][x++] && x + 1 < (int)ft_strlen(map[y]))
		if (ft_checkside(map[y][x]))
			return (ft_poserr(y, x, "Carte invalide (ni ' ' ni '1') sur les \
contours de la carte: "));
	while (map[y--][x] && y > 0)
		if (ft_checkside(map[y][x]))
			return (ft_poserr(y, x, "Carte invalide (ni ' ' ni '1') sur les \
contours de la carte: "));
	while (map[y][x--] && x > 0)
		if (ft_checkside(map[y][x]))
			return (ft_poserr(y, x, "Carte invalide (ni ' ' ni '1') sur les \
contours de la carte: "));
	return (0);
}

int	ft_valid_map(t_info *info)
{
	if (!info->map)
		return (ft_putstr_error("Error\nMap error\n"));
	if (ft_elems(info->map) || ft_nb_player(info->map))
		return (1);
	if (ft_sides(info->map))
		return (1);
	if (ft_spaces(info->map) || ft_zero(info->map))
		return (1);
	return (0);
}
