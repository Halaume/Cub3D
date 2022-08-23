/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove_right.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 11:40:44 by ghanquer          #+#    #+#             */
/*   Updated: 2022/08/05 17:46:40 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	mv_right_y(t_info *info)
{
	if (sin(info->player.angle - (M_PI / 2)) > 0)
	{
		if (!is_wall(info, (info->player.y - (sin(info->player.angle - \
								(M_PI / 2)) * (0.25)) - 0.1), info->player.x))
			info->player.y -= (sin(info->player.angle - (M_PI / 2)) * 0.25);
		else
			info->player.y = floor(info->player.y) + 0.1;
	}
	else
	{
		if (!is_wall(info, (info->player.y - (sin(info->player.angle - \
								(M_PI / 2)) * (0.25)) + 0.1), info->player.x))
			info->player.y -= (sin(info->player.angle - (M_PI / 2)) * 0.25);
		else
			info->player.y = ceil(info->player.y) - 0.1;
	}
}

void	mv_right_x(t_info *info, double oldy)
{
	(void)oldy;
	if (cos(info->player.angle - (M_PI / 2)) > 0)
	{
		if (!is_wall(info, oldy, (info->player.x + (cos(info->player.angle - \
								(M_PI / 2)) * (0.25)) + 0.1)))
			info->player.x += (cos(info->player.angle - (M_PI / 2)) * 0.25);
		else
			info->player.x = ceil(info->player.x) - 0.1;
	}
	else
	{
		if (!is_wall(info, oldy, (info->player.x + (cos(info->player.angle - \
								(M_PI / 2)) * (0.25)) - 0.1)))
			info->player.x += (cos(info->player.angle - (M_PI / 2)) * 0.25);
		else
			info->player.x = floor(info->player.x) + 0.1;
	}
}

void	mv_right(t_info *info)
{
	double	oldy;
	double	oldx;

	oldy = info->player.y;
	oldx = info->player.x;
	mv_right_y(info);
	mv_right_x(info, oldy);
	if (is_wall(info, info->player.y, info->player.x))
	{
		info->player.y = oldy;
		info->player.x = oldx;
	}
}
