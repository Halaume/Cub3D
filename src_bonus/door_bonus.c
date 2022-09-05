/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:10:41 by ghanquer          #+#    #+#             */
/*   Updated: 2022/09/05 16:12:43 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

void	check_door_text(t_info *info, t_casting *cast)
{
	if (cast->is_wall == 3)
	{
		cast->percent = (cast->curr[0] - floor(cast->curr[0])) / 1;
		cast->texture = *info->texture_d;
		if (cast->ray[1] > 0)
			cast->percent = 1 - cast->percent;
	}
	else if (cast->is_wall == 4)
	{
		cast->texture = *info->texture_d;
		cast->percent = (cast->curr[1] - floor(cast->curr[1])) / 1;
		if (cast->ray[0] < 0)
			cast->percent = 1 - cast->percent;
	}
}

double	get_next_x(t_info *info)
{
	double	x;

	if (cos(info->player.angle) > 0)
		x = (info->player.x + cos(info->player.angle) * (0.25) + 0.1);
	else
		x = (info->player.x + cos(info->player.angle) * (0.25) - 0.1);
	return (x);
}

double	get_next_y(t_info *info)
{
	double	y;

	if (sin(info->player.angle) > 0)
		y = (info->player.y - (sin(info->player.angle) * (0.25)) - 0.1);
	else
		y = (info->player.y - (sin(info->player.angle) * (0.25)) + 0.1);
	return (y);
}

void	close_door(t_info *info, t_door *door)
{
	if (!((int)info->player.x == door->x && (int)info->player.y == door->y))
		door->is_op = 0;
}

void	open_door(t_info *info)
{
	double	x;
	double	y;
	t_door	*my_door;

	x = get_next_x(info);
	y = get_next_y(info);
	if (info->map[(int)y][(int)x] == '2')
	{
		my_door = get_this_door(info->door, (int)x, (int)y);
		if (my_door == NULL)
		{
			printf("Unable to find this door %d:%d\n", (int)x, (int)y);
			return ;
		}
		if (my_door->is_op == 0)
		{
			my_door->is_op = 1;
			my_door->last_open = get_now(info);
		}
		else
			close_door(info, my_door);
	}
}
