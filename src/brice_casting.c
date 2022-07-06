/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brice_casting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:37:14 by ghanquer          #+#    #+#             */
/*   Updated: 2022/07/06 17:36:25 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	get_proj_screen(t_info *info, t_casting *cast)
{
	cast->proj_screen[0] = info->player.angle + (M_PI / 4);
	cast->proj_screen[1] = (-sin(cast->proj_screen[0])) * \
						((double)cast->proj_dist / cos(M_PI / 4)) + \
						info->player.y;
	cast->proj_screen[0] = (cos(cast->proj_screen[0])) * \
						((double)cast->proj_dist / cos(M_PI / 4)) + \
						info->player.x;
	cast->proj_screen[2] = info->player.angle - (M_PI / 4);
	cast->proj_screen[3] = (-sin(cast->proj_screen[2])) * \
						((double)cast->proj_dist / cos(M_PI / 4)) + \
						info->player.y;
	cast->proj_screen[2] = (cos(cast->proj_screen[2])) * \
						((double)cast->proj_dist / cos(M_PI / 4)) + \
						info->player.x;
}

void	next_curr(t_casting *cast, int side)
{
	double	tmp[2];
	int		autre;

	autre = cast->side ^ 1;
	if (cast->ray[side] < 0)
		tmp[side] = cast->curr[side] - 1;
	else
		tmp[side] = cast->curr[side] + 1;
	cast->delta[side] = fabs(tmp[side] - cast->curr[side]) / \
						fabs(cast->ray[side]);
	if (cast->ray[autre] < 0)
		tmp[autre] = floor(cast->curr[autre]) - 0.0001;
	else
		tmp[autre] = ceil(cast->curr[autre]);
	cast->delta[autre] = fabs(tmp[autre] - cast->curr[autre]) / \
						fabs(cast->ray[autre]);
	if (fabs(cast->delta[autre]) < 0.0001)
		tmp[autre] += 0.0001;
	cast->delta[autre] = fabs(tmp[autre] - cast->curr[autre]) / \
						fabs(cast->ray[autre]);
	cast->curr[0] = tmp[0];
	cast->curr[1] = tmp[1];
}

void	choose_texture(t_info *info, t_casting *cast)
{
	if (cast->is_wall == 1)
	{
		cast->percent = (cast->curr[0] - floor(cast->curr[0])) / 1;
		cast->texture = info->texture_n;
		if (cast->ray[1] > 0)
		{
			cast->texture = info->texture_s;
			cast->percent = 1 - cast->percent;
		}
	}
	else
	{
		cast->texture = info->texture_e;
		cast->percent = (cast->curr[1] - floor(cast->curr[1])) / 1;
		if (cast->ray[0] < 0)
		{
			cast->texture = info->texture_w;
			cast->percent = 1 - cast->percent;
		}
	}
	if (cast->percent >= 1)
		cast->percent = 0.9999;
	cast->percent = floor(cast->percent * (double)cast->texture.width);
}

void	do_it_pls(t_info *info, t_casting *cast, int i)
{
	choose_texture(info, cast);
	if (cast->wall_height < 0)
		cast->start_px = 1;
	else
		cast->start_px = (int)floor((((double)info->h - 1) / 2) - \
				((double)cast->wall_height / 2));
	if (cast->wall_height >= info->h)
		cast->end_px = info->h;
	else
		cast->end_px = cast->start_px + cast->wall_height - 1;
	put_col(info, cast, i);
}

void	get_the_wall(t_info *info, t_casting *cast, int i)
{
	if (fabs(cast->curr[0] - info->player.x) < 0.0001)
		cast->distance0 = fabs(cast->curr[1] - info->player.y);
	else if (fabs(cast->curr[1] - info->player.y) < 0.0001)
		cast->distance0 = fabs(cast->curr[0] - info->player.x);
	else
		cast->distance0 = hypot(fabs(cast->curr[0] - info->player.x), \
				fabs(cast->curr[1] - info->player.y));
	if (fabs(cast->ray[0]) < 0.0001)
		cast->distance1 = fabs(cast->ray[1]);
	else if (fabs(cast->ray[1]) < 0.0001)
		cast->distance1 = fabs(cast->ray[0]);
	else
		cast->distance1 = hypot(fabs(cast->ray[0]), fabs(cast->ray[1]));
	cast->wall_ratio = cast->distance1 / cast->distance0;
	cast->wall_height = (int)round(cast->wall_ratio * ((double)info->w / 2));
	do_it_pls(info, cast, i);
}

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
	cast.dir_v_x = (cast.proj_screen[2] - cast.proj_screen[0]) / \
				(double)(info->w - 1);
	cast.dir_v_y = (cast.proj_screen[3] - cast.proj_screen[1]) / \
				(double)(info->w - 1);
	i = -1;
	cast.side = 0;
	while (++i < info->w)
	{
		cast.ray[0] = (cast.proj_screen[0] + cast.dir_v_x * i) - info->player.x;
		cast.ray[1] = (cast.proj_screen[1] + cast.dir_v_y * i) - info->player.y;
		cast.curr[0] = info->player.x;
		if (fabs(cast.ray[0]) > 0.0001)
		{
			if (cast.ray[0] < -0.0001)
				cast.curr[0] = floor(info->player.x) - 0.0001;
			else
				cast.curr[0] = ceil(info->player.x);
			cast.delta[0] = fabs(cast.curr[0] - info->player.x) / fabs(cast.ray[0]);
		}
		cast.curr[1] = info->player.y;
		if (fabs(cast.ray[1]) > 0.0001)
		{
			if (cast.ray[1] < -0.0001)
				cast.curr[1] = floor(info->player.y) - 0.0001;
			else
				cast.curr[1] = ceil(info->player.y);
			cast.delta[1] = fabs(cast.curr[1] - info->player.y) / fabs(cast.ray[1]);
		}
		cast.prev_x = info->player.x;
		cast.prev_y = info->player.y;
		cast.is_wall = 0;
		while (cast.is_wall == 0)
		{
			if (fabs(cast.ray[0]) < 0.0001 || fabs(cast.ray[1]) < 0.0001)
				cast_droit(info, &cast);
			else
				cast_angle(info, &cast);
		}
		get_the_wall(info, &cast, i);
	}
	mlx_put_image_to_window(info->mlx, info->window, info->img.img, 0, 0);
}
