/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:12:32 by ghanquer          #+#    #+#             */
/*   Updated: 2022/08/28 15:37:37 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

void	put_the_wall_exit(t_info *info, t_casting *cast, int *i)
{
	cast->current = (double)(*i - cast->start_px) * cast->step;
	cast->percent_y = (int)cast->current;
	unsigned int	tmp;
	while (*i < cast->end_px && *i < info->h)
	{
		cast->percent_y = (int)cast->current;
		if (cast->percent_y == cast->texture.height)
			cast->percent_y = cast->texture.height - 1;
		tmp = *(unsigned int *)(cast->origin + \
				(int)cast->percent_y * cast->texture.img.line_length);
		if (!(tmp >> 24))
			*(unsigned int *)cast->dist = tmp;
		cast->dist += info->img.line_length;
		cast->current += cast->step;
		*i += 1;
	}
}

void	put_col_exit(t_info *info, t_casting *cast, int y)
{
	int		i;

	cast->dist = info->img.addr + y * (info->img.bits_per_pixel / 8);
	cast->origin = cast->texture.img.addr + (int)cast->percent * \
				(cast->texture.img.bits_per_pixel / 8);
	cast->step = ((double)1 / (double)cast->wall_height) * \
		(double)(cast->texture.height);
	i = 0;
	while (i < cast->start_px)
	{
		*(unsigned int *)cast->dist = info->color_sky;
		cast->dist += info->img.line_length;
		i++;
	}
	put_the_wall_exit(info, cast, &i);
	while (i < info->h)
	{
		*(unsigned int *)cast->dist = info->color_floor;
		cast->dist += info->img.line_length;
		i++;
	}
}

void	pls_help_exit(t_info *info, t_casting *cast, int i)
{
	cast->texture = *info->texture_ex;
	if (cast->exit_state == 3)
	{
		cast->percent = (cast->curr[0] - floor(cast->curr[0])) / 1;
		if (cast->ray[1] > 0)
			cast->percent = 1 - cast->percent;
	}
	else if (cast->exit_state == 4)
	{
		cast->percent = (cast->curr[1] - floor(cast->curr[1])) / 1;
		if (cast->ray[0] < 0)
			cast->percent = 1 - cast->percent;
	}
	if (cast->percent >= 1)
		cast->percent = 0.9999;
	cast->percent = floor(cast->percent * (double)cast->texture.width);
	if (cast->wall_height < 0)
		cast->start_px = 1;
	else
		cast->start_px = (int)floor((((double)info->h - 1) / 2) - \
				((double)cast->wall_height / 2));
	if (cast->wall_height >= info->h)
		cast->end_px = info->h;
	else
		cast->end_px = cast->start_px + cast->wall_height - 1;
	put_col_exit(info, cast, i);
}

void	get_the_exit(t_info *info, t_casting *cast, int i)
{
	if (cast->exit[0] == 0 || cast->exit[1] == 0)
		return ;
	else
	{
		cast->curr[0] = cast->exit[0];
		cast->curr[1] = cast->exit[1];
		cast->ray[0] = cast->exit_ray[0];
		cast->ray[1] = cast->exit_ray[1];
	}
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
	pls_help_exit(info, cast, i);
}
