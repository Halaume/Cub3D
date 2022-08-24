/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_tools_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 12:12:42 by nflan             #+#    #+#             */
/*   Updated: 2022/08/24 11:11:12 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

int	ft_valid_elems(char c)
{
	if (c != 'W' && c != 'N' && c != 'S' && c != 'E' && c != ' ' && c != '1'
		&& c != '0' && c != '2')
		return (1);
	return (0);
}

int	ft_check_around(char **map, int y, int x)
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
		if (ft_check_around(map, y - 1, x))
			return (1);
	if (y + 1 < (int)ft_tablen(map))
		if (ft_check_around(map, y + 1, x))
			return (1);
	if (x - 1 >= 0)
		if (map[y][x - 1] == ' ')
			return (1);
	if (x + 1 < (int)ft_strlen(map[0]))
		if (map[y][x + 1] == ' ')
			return (1);
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
