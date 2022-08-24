/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:51:30 by nflan             #+#    #+#             */
/*   Updated: 2022/08/24 18:18:26 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

int	ft_charcheck(t_info *info, char **map, int y, int x)
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
	else if (map[y][x] == 'X')
		info->is_exit = 1;
	if (nb > 1)
		return (ft_putstr_error("Error\nTrop de joueurs sur la carte\n"));
	return (0);
}

int	ft_parsingage(t_info *info)
{
	int	x;
	int	y;

	y = 0;
	while (info->map[y])
	{
		x = 0;
		while (info->map[y][x])
		{
			if (ft_charcheck(info, info->map, y, x))
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

int	ft_check_doex(t_info *info)
{
	if (!info->door && info->texture_d.path)
		return (ft_putstr_error("Error\nTexture pour la porte mais pas de porte\
 dans la carte\n"));
	if (info->door && !info->texture_d.path)
		return (ft_putstr_error("Error\nPorte(s) dans la map mais pas de \
texture\n"));
	if (info->is_exit && !info->texture_ex.path)
		return (ft_putstr_error("Error\nSortie(s) dans la map mais pas de \
texture\n"));
	if (!info->is_exit && info->texture_ex.path)
		return (ft_putstr_error("Error\nTexture pour la sortie mais pas de \
sortie dans la carte\n"));
	return (0);
}

int	ft_valid_map(t_info *info)
{
	if (!info->map)
		return (ft_putstr_error("Error\nMap error\n"));
	if (ft_sides(info->map) || ft_parsingage(info))
		return (1);
	if (ft_doors(info, 1))
		return (1);
	if (ft_doors(info, 2))
		return (1);
	return (ft_check_doex(info));
}
