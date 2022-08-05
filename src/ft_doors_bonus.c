/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_doors_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 15:24:09 by nflan             #+#    #+#             */
/*   Updated: 2022/08/05 15:39:40 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include "../inc/cub3d.h"

int	ft_check_doors(char **map, int y, int x)
{
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
					return (ft_poserr(y, x, "Carte invalide (les murs autour de\
 la porte sont inexistants ou mal positionnes): "));
			}
			x++;
		}
		y++;
	}
	return (0);
}*/
