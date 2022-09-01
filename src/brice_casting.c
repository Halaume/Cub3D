/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brice_casting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:37:14 by ghanquer          #+#    #+#             */
/*   Updated: 2022/09/01 11:34:09 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	cast_droit(t_info *info, t_casting *cast)
{
	if (fabs(cast->ray[0]) < 0.0001)
	{
		if (info->map[(int)cast->curr[1]][(int)cast->curr[0]] == '1')
			cast->is_wall = 1;
		else
		{
			cast->curr[1] += 1;
			if (cast->ray[1] < 0)
				cast->curr[1] -= 2;
		}
	}
	else
	{
		if (info->map[(int)cast->curr[1]][(int)cast->curr[0]] == '1')
			cast->is_wall = 2;
		else
		{
			cast->curr[0] += 1;
			if (cast->ray[0] < 0)
				cast->curr[0] -= 2;
		}
	}
}

void	cast_angle(t_info *info, t_casting *cast)
{
	if (fabs(cast->delta[0] - cast->delta[1]) < 0.0001 || \
			cast->delta[0] < cast->delta[1])
	{
		cast->curr[1] = cast->delta[0] * cast->ray[1] + cast->prev_y;
		cast->side = 0;
		if (info->map[(int)cast->curr[1]][(int)cast->curr[0]] == '1')
			cast->is_wall = 2;
	}
	else
	{
		cast->curr[0] = cast->delta[1] * cast->ray[0] + cast->prev_x;
		cast->side = 1;
		if (info->map[(int)cast->curr[1]][(int)cast->curr[0]] == '1')
			cast->is_wall = 1;
	}
	if (cast->is_wall == 0)
	{
		cast->prev_x = cast->curr[0];
		cast->prev_y = cast->curr[1];
		next_curr(cast, cast->side);
	}
}

void	casting2(t_info *info, t_casting *cast, int i)
{
	cast->ray[0] = (cast->proj_screen[0] + cast->dir_v_x * i) - info->player.x;
	cast->ray[1] = (cast->proj_screen[1] + cast->dir_v_y * i) - info->player.y;
	cast->curr[0] = info->player.x;
	if (fabs(cast->ray[0]) > 0.0001)
	{
		if (cast->ray[0] < -0.0001)
			cast->curr[0] = floor(info->player.x) - 0.0001;
		else
			cast->curr[0] = ceil(info->player.x);
		cast->delta[0] = fabs(cast->curr[0] - info->player.x) / \
						fabs(cast->ray[0]);
	}
	cast->curr[1] = info->player.y;
	if (fabs(cast->ray[1]) > 0.0001)
	{
		if (cast->ray[1] < -0.0001)
			cast->curr[1] = floor(info->player.y) - 0.0001;
		else
			cast->curr[1] = ceil(info->player.y);
		cast->delta[1] = fabs(cast->curr[1] - info->player.y) / \
						fabs(cast->ray[1]);
	}
	cast->prev_x = info->player.x;
	cast->prev_y = info->player.y;
	cast->is_wall = 0;
}

void	brice_casting(t_info *info)
{
	int			i;
	t_casting	cast;

	cast.proj_dist = 1;
	if (fabs(info->player.angle + M_PI / 2) < 0.0001)
		info->player.angle = 3 * M_PI * 2;
	else if (fabs(info->player.angle) < 0.0001)
		info->player.angle = 2 * M_PI;
	get_proj_screen(info, &cast);
	i = -1;
	cast.side = 0;
	while (++i < info->w)
	{
		casting2(info, &cast, i);
		while (cast.is_wall == 0)
		{
			if (fabs(cast.ray[0]) < 0.0001 || fabs(cast.ray[1]) < 0.0001)
				cast_droit(info, &cast);
			else
				cast_angle(info, &cast);
		}
		get_the_wall(info, &cast, i);
	}
	mlx_put_image_to_window(info->mlx, info->window,
		info->img[info->cur_i].img, 0, 0);
}
