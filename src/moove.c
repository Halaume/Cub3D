/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 10:43:10 by ghanquer          #+#    #+#             */
/*   Updated: 2022/07/05 17:19:53 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	is_wall(t_info *info, double y, double x)
{
	if (y > info->nb_line || x > info->nb_col || x < 0 || y < 0)
		return (1);
	if (info->map[(int)y][(int)x] == '1')
		return (1);
	return (0);
}

void	mv_left_y(t_info *info)
{
	if (sin(info->player.angle + (M_PI / 2)) > 0)
	{
		if (!is_wall(info, (info->player.y - (sin(info->player.angle + \
								(M_PI / 2)) * (0.25)) - 0.1), info->player.x))
			info->player.y -= (sin(info->player.angle + (M_PI / 2)) * 0.25);
		else
			info->player.y = floor(info->player.y) + 0.1;
	}
	else
	{
		if (!is_wall(info, (info->player.y - (sin(info->player.angle + \
								(M_PI / 2)) * (0.25)) + 0.1), info->player.x))
			info->player.y -= (sin(info->player.angle + (M_PI / 2)) * 0.25);
		else
			info->player.y = ceil(info->player.y) - 0.1;
	}
}

void	mv_left_x(t_info *info, double oldy)
{
	if (cos(info->player.angle + (M_PI / 2)) > 0)
	{
		if (!is_wall(info, oldy, (info->player.x + (cos(info->player.angle + \
								(M_PI / 2)) * (0.25)) + 0.1)))
			info->player.x += (cos(info->player.angle + (M_PI / 2)) * 0.25);
		else
			info->player.x = ceil(info->player.x) - 0.1;
	}
	else
	{
		if (!is_wall(info, oldy, (info->player.x + (cos(info->player.angle + \
								(M_PI / 2)) * (0.25)) - 0.1)))
			info->player.x += (cos(info->player.angle + (M_PI / 2)) * 0.25);
		else
			info->player.x = floor(info->player.x) + 0.1;
	}
}

void	mv_left(t_info *info)
{
	double	oldy;
	double	oldx;

	oldy = info->player.y;
	oldx = info->player.x;
	mv_left_y(info);
	mv_left_x(info, oldy);
	if (is_wall(info, info->player.x, info->player.y))
	{
		info->player.y = oldy;
		info->player.x = oldx;
	}
}

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
	if (is_wall(info, info->player.x, info->player.y))
	{
		info->player.y = oldy;
		info->player.x = oldx;
	}
}

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
	if (is_wall(info, info->player.x, info->player.y))
	{
		info->player.y = oldy;
		info->player.x = oldx;
	}
}

void	mv_forward_y(t_info *info)
{
	if (sin(info->player.angle) > 0)
	{
		if (!is_wall(info, (info->player.y - (sin(info->player.angle) * \
							(0.25)) - 0.1), info->player.x))
			info->player.y -= (sin(info->player.angle) * 0.25);
		else
			info->player.y = floor(info->player.y) + 0.1;
	}
	else
	{
		if (!is_wall(info, (info->player.y - (sin(info->player.angle) * \
							(0.25)) + 0.1), info->player.x))
			info->player.y -= (sin(info->player.angle) * 0.25);
		else
			info->player.y = ceil(info->player.y) - 0.1;
	}
}

void	mv_forward_x(t_info *info, double oldy)
{
	if (cos(info->player.angle) > 0)
	{
		if (!is_wall(info, oldy, (info->player.x + cos(info->player.angle) * \
						(0.25) + 0.1)))
			info->player.x += (cos(info->player.angle) * 0.25);
		else
			info->player.x = ceil(info->player.x) - 0.1;
	}
	else
	{
		if (!is_wall(info, oldy, (info->player.x + cos(info->player.angle) * \
						(0.25) - 0.1)))
			info->player.x += (cos(info->player.angle) * 0.25);
		else
			info->player.x = floor(info->player.x) + 0.1;
	}
}

void	mv_for(t_info *info)
{
	double	oldy;
	double	oldx;

	oldy = info->player.y;
	oldx = info->player.x;
	mv_forward_y(info);
	mv_forward_x(info, oldy);
	if (is_wall(info, info->player.x, info->player.y))
	{
		info->player.y = oldy;
		info->player.x = oldx;
	}
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
