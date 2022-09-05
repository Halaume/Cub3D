/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting_tools_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 11:31:25 by ghanquer          #+#    #+#             */
/*   Updated: 2022/09/05 16:18:25 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

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
	cast->dir_v_x = (cast->proj_screen[2] - cast->proj_screen[0]) / \
				(double)(info->w - 1);
	cast->dir_v_y = (cast->proj_screen[3] - cast->proj_screen[1]) / \
				(double)(info->w - 1);
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

void	choose_texture(t_info *info, t_casting *cast)
{
	check_door_text(info, cast);
	if (cast->is_wall == 1)
	{
		cast->percent = (cast->curr[0] - floor(cast->curr[0])) / 1;
		cast->texture = *info->texture_n;
		if (cast->ray[1] > 0)
		{
			cast->texture = *info->texture_s;
			cast->percent = 1 - cast->percent;
		}
	}
	else if (cast->is_wall == 2)
	{
		cast->texture = *info->texture_e;
		cast->percent = (cast->curr[1] - floor(cast->curr[1])) / 1;
		if (cast->ray[0] < 0)
		{
			cast->texture = *info->texture_w;
			cast->percent = 1 - cast->percent;
		}
	}
	if (cast->percent >= 1)
		cast->percent = 0.9999;
	cast->percent = floor(cast->percent * (double)cast->texture.width);
}

void	do_it_pls(t_info *info, t_casting *cast, int i)
{
	check_angle(info, cast);
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
	get_the_exit(info, cast);
	if (cast->do_exit == 1)
		put_the_wall_exit(info, cast, i);
}
