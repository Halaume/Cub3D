/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 10:43:10 by ghanquer          #+#    #+#             */
/*   Updated: 2022/08/31 10:51:15 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

t_door	*get_this_door(t_door *list, int x, int y)
{
	t_door	*tmp;

	tmp = list;
	while (tmp && !(tmp->x == x && tmp->y == y))
		tmp = tmp->next;
	return (tmp);
}

int	is_door_open(t_info *info, int y, int x)
{
	t_door	*this_door;

	this_door = get_this_door(info->door, x, y);
	if (this_door == NULL)
		return (0);
	if (this_door->is_op == 0)
		return (1);
	return (0);
}

int	is_wall(t_info *info, double y, double x)
{
	if ((int)y > info->nb_line || (int)x > info->nb_col || (int)x < 0
		|| (int)y < 0)
		return (1);
	if (info->map[(int)y][(int)x] == '1')
		return (1);
	if (info->map[(int)y][(int)x] == '2' && is_door_open(info, (int)y, (int)x) == 1)
		return (1);
	return (0);
}

void	turn_right(t_info *info)
{
	info->player.angle -= (5 * M_PI) / 180;
	if (info->player.angle == 2 * M_PI)
		info->player.angle = 0;
}

void	turn_left(t_info *info)
{
	info->player.angle += ((5 * M_PI) / 180);
	if (info->player.angle == 2 * M_PI)
		info->player.angle = 0;
}
