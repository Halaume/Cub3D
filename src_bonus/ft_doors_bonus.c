/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_doors_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 15:24:09 by nflan             #+#    #+#             */
/*   Updated: 2022/08/24 11:47:06 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//	TODO
//	Chain list -> pos x/y of door -> state Open/Close -> time last open
#include "../inc/cub3d_bonus.h"

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

	i = 0;
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

void	ft_dooradd_back(t_door **door, t_door *new)
{
	t_door	*tmp;

	tmp = *door;
	if (door && new)
	{
		if (*door == NULL)
			*door = new;
		else
		{
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
	}
}

int	ft_doornew(t_door **door, int x, int y)
{
	t_door	*new;

	new = ft_calloc(sizeof(t_door), 1);
	if (!new)
		return (ft_putstr_error("Error\nMalloc error\n"));
	new->x = x;
	new->y = y;
	ft_dooradd_back(door, new);
	return (0);
}

int	ft_doors(t_info *info, int i)
{
	int	x;
	int	y;

	y = 0;
	while (info->map[y])
	{
		x = 0;
		while (info->map[y][x])
		{
			if (info->map[y][x] == '2')
			{
				if (i == 1)
				{
					if (ft_check_doors(info->map, y, x))
						return (1);
				}
				else if (i == 2)
					if (ft_doornew(&info->door, x, y))
						return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}
