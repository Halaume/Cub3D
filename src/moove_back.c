/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove_back.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 11:43:30 by ghanquer          #+#    #+#             */
/*   Updated: 2022/08/05 17:47:08 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	mv_back_y(t_info *info)
{
	if (sin(info->player.angle) < 0)
	{
		if (!is_wall(info, (info->player.y + (sin(info->player.angle) * \
							(0.25)) - 0.1), info->player.x))
			info->player.y += (sin(info->player.angle) * 0.25);
		else
			info->player.y = floor(info->player.y) + 0.1;
	}
	else
	{
		if (!is_wall(info, (info->player.y + (sin(info->player.angle) * \
							(0.25)) + 0.1), info->player.x))
			info->player.y += (sin(info->player.angle) * 0.25);
		else
			info->player.y = ceil(info->player.y) - 0.1;
	}
}

void	mv_back_x(t_info *info, double oldy)
{
	if (cos(info->player.angle) < 0)
	{
		if (!is_wall(info, oldy, (info->player.x - cos(info->player.angle) * \
						(0.25) + 0.1)))
			info->player.x -= (cos(info->player.angle) * 0.25);
		else
			info->player.x = ceil(info->player.x) - 0.1;
	}
	else
	{
		if (!is_wall(info, oldy, (info->player.x - cos(info->player.angle) * \
						(0.25) - 0.1)))
			info->player.x -= (cos(info->player.angle) * 0.25);
		else
			info->player.x = floor(info->player.x) + 0.1;
	}
}

void	mv_back(t_info *info)
{
	double	oldy;
	double	oldx;

	oldy = info->player.y;
	oldx = info->player.x;
	mv_back_y(info);
	mv_back_x(info, oldy);
	if (is_wall(info, info->player.y, info->player.x))
	{
		info->player.y = oldy;
		info->player.x = oldx;
	}
}
