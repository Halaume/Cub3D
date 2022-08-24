/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:10:41 by ghanquer          #+#    #+#             */
/*   Updated: 2022/08/24 14:19:53 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

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
	if ((int)info->player.x != door->x && (int)info->player.y != door->y)
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
			my_door->is_op = 1;
		else
			close_door(info, my_door);
	}
}

/*unsigned long long	get_now(t_info *info)
{
	unsigned long long	now;
	struct	timeval	get_time;

	gettimeofday(get_time, NULL);
	now = ((get_time.tv_sec - 1 - info->start.tv_sec) * 1000000) + \
			1000000 + (get_time.tv_usec - info->start.tv_usec);
	now = now / 1000;
	return (now);
}*/
