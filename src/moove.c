/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 10:43:10 by ghanquer          #+#    #+#             */
/*   Updated: 2022/08/22 11:18:32 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*t_door	*get_this_door(t_door *list, int x, int y)
{
	t_door	*tmp;

	tmp = list;
	while (tmp->x != x && tmp->y != y)
		tmp = tmp-next;
	return (tmp);
}

int	is_door_open(t_info *info, int y, int x)
{
	t_door	*this_door;

	this_door = get_this_door(info->door, x, y);
	if (this_door == NULL)
		return (-1);
	if (this_door->state = 1)
		return (1);
	return (0);
}*/

int	is_wall(t_info *info, double y, double x)
{
	if ((int)y > info->nb_line || (int)x > info->nb_col || (int)x < 0
		|| (int)y < 0)
		return (1);
	if (info->map[(int)y][(int)x] == '1')
		return (1);
//	if (info->map[(int)y][(int)x] == '2' && is_door_open(info, (int)y, (int)x) == 1)
//		return (1);
//	if (is_door_open(info, (int)y, (int)x) == -1)
//		return (printf("error, door not exist\n"), 1);
	return (0);
}

void	turn_right(t_info *info)
{
	info->player.angle -= ((5 * M_PI) / 180);
	if (info->player.angle == 2 * M_PI)
		info->player.angle = 0;
}

void	turn_left(t_info *info)
{
	info->player.angle += ((5 * M_PI) / 180);
	if (info->player.angle == 2 * M_PI)
		info->player.angle = 0;
}
