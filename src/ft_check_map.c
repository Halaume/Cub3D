/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:51:30 by nflan             #+#    #+#             */
/*   Updated: 2022/08/04 18:48:03 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_poserr(int y, int x, char *str)
{
	char	*pos;

	pos = NULL;
	ft_putstr_error("Error\n");
	ft_putstr_error(str);
	pos = ft_itoa(x);
	if (!pos)
		return (1);
	ft_putstr_error(pos);
	free(pos);
	ft_putstr_error(", ");
	pos = ft_itoa(y);
	if (!pos)
		return (1);
	ft_putstr_error(pos);
	free(pos);
	ft_putstr_error("'\n");
	return (1);
}

int	ft_nb_player(char **map)
{
	int	nb;
	int	x;
	int	y;

	nb = 0;
	y = 0;
	while (map[y] && nb <= 1)
	{
		x = 0;
		while (map[y][x] && nb <= 1)
		{
			if (map[y][x] == 'W' || map[y][x] == 'N'
				|| map[y][x] == 'S' || map[y][x] == 'E')
				nb++;
			x++;
		}
		y++;
	}
	if (nb > 1)
		return (ft_putstr_error("Error\nTrop de joueurs sur la carte\n"));
	return (0);
}

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
				return (ft_poserr(y, x, "Carte invalide (mauvais caractere) en \
(x,y): '"));
			x++;
		}
		y++;
	}
	return (0);
}

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
					return (ft_poserr(y, x, "Carte invalide en (x,y): '"));
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
					return (ft_poserr(y, x, "Carte invalide en (x,y): '"));
			}
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
			return (ft_poserr(y, x, "Carte invalide en (x,y): '"));
	while (map[y][x++] && x + 1 < (int)ft_strlen(map[y]))
		if (ft_checkside(map[y][x]))
			return (ft_poserr(y, x, "Carte invalide en (x,y): '"));
	while (map[y--][x] && y > 0)
		if (ft_checkside(map[y][x]))
			return (ft_poserr(y, x, "Carte invalide en (x,y): '"));
	while (map[y][x--] && x > 0)
		if (ft_checkside(map[y][x]))
			return (ft_poserr(y, x, "Carte invalide en (x,y): '"));
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
