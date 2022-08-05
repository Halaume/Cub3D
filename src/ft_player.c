/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 12:14:50 by nflan             #+#    #+#             */
/*   Updated: 2022/08/05 12:19:54 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

void	ft_init_player_angle(t_info *info, int y, int x)
{
	if (info->map[y][x] == 'N')
		info->player.angle = M_PI / 2;
	else if (info->map[y][x] == 'S')
		info->player.angle = M_PI * 1.5;
	else if (info->map[y][x] == 'W')
		info->player.angle = M_PI;
	else if (info->map[y][x] == 'E')
		info->player.angle = M_PI * 2;
}

int	new_init_player(t_info *info)
{
	int			x;
	int			y;
	char		**tab;

	tab = info->map;
	y = 0;
	while (tab[y])
	{
		x = 0;
		while (tab[y][x] && (tab[y][x] != 'W' && tab[y][x] != 'N'
				&& tab[y][x] != 'S' && tab[y][x] != 'E'))
			x++;
		if (tab[y][x])
			break ;
		y++;
	}
	if (!tab[y])
		return (free_func(info), ft_putstr_error("Error\nJoueur introuvable\n"));
	info->player.x = x;
	info->player.y = y;
	ft_init_player_angle(info, y, x);
	return (0);
}
