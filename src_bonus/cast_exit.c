/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:12:32 by ghanquer          #+#    #+#             */
/*   Updated: 2022/08/29 18:15:53 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

double	distance(double x0, double y0, double x1, double y1)
{
	if (fabs(x1 - x0) < 0.0001)
		return (fabs(y1 - y0));
	if (fabs(y1 - y0) < 0.0001)
		return (fabs(x1 - x0));
	return (hypot(fabs(x1 - x0), fabs(y1 - y0)));
}

double	vector_angle(double v0[2], double v1[2])
{
	double	angle;

	angle = acos((v0[0] * v1[0] + v0[1] * v1[1]) \
			/ (distance(0, 0, v0[0], v0[1]) * distance(0, 0, v1[0], v1[1])));
	return (angle);
}

void	init_exit(t_info *info, t_casting * cast)
{
	double	ratio;

	cast->texture_ex = *info->texture_ex;
	cast->curr[0] = cast->exit[0];
	cast->curr[1] = cast->exit[1];
	cast->ray[0] = cast->exit_ray[0];
	cast->ray[1] = cast->exit_ray[1];
	cast->exit_mid[0] = floor(cast->curr[0]) + 0.5;
	cast->exit_mid[1] = floor(cast->curr[1]) + 0.5;
	cast->exit_dist = distance(info->player.x, info->player.y, cast->exit_mid[0], cast->exit_mid[1]);
	cast->exit_ray[0] = -(cast->exit_mid[1] - info->player.y);
	cast->exit_ray[1] = cast->exit_mid[0] - info->player.x;
	ratio = sqrt(pow(0.5, 2) / (pow(cast->exit_ray[0], 2) + pow(cast->exit_ray[1], 2)));
	cast->exit_ends[0] = ratio * cast->exit_ray[0] + cast->exit_mid[0];
	cast->exit_ends[1] = ratio * cast->exit_ray[1] + cast->exit_mid[1];
	cast->exit_ends[2] = -ratio * cast->exit_ray[0] + cast->exit_mid[0];
	cast->exit_ends[3] = -ratio * cast->exit_ray[1] + cast->exit_mid[1];
	cast->exit_ray[0] = cast->exit_mid[0] - info->player.x;
	cast->exit_ray[1] = cast->exit_mid[1] - info->player.y;
}

void	put_col_exit(t_info *info, t_casting *cast, int *i, int y, double *current)
{

	cast->dist = info->img.addr + y * (info->img.bits_per_pixel / 8);
	cast->origin = cast->texture_ex.img.addr + (int)cast->percent_ex * \
				(cast->texture_ex.img.bits_per_pixel / 8);
	if (cast->start_px_ex < 0)
	{
		*i = 0;
		*current = (double)(*i - cast->start_px_ex) * cast->step_ex;
	}
	else
	{
		*i = cast->start_px_ex;
		*current = 0;
	}
	cast->dist += info->img.line_length * *i;
}

void	put_the_wall_exit(t_info *info, t_casting *cast, int y)
{
	int				i;
	int				percent_y;
	unsigned int	tmp;
	double			current;

	put_col_exit(info, cast, &i, y, &current);
	while (i <= cast->end_px_ex && i < info->h)
	{
		percent_y = (int)current;
		if (percent_y == cast->texture_ex.height)
			percent_y = cast->texture_ex.height - 1;
		tmp = *(unsigned int *)(cast->origin + \
				(int)percent_y * cast->texture_ex.img.line_length);
		if (!(tmp >> 24))
			*(unsigned int *)cast->dist = tmp;
		cast->dist += info->img.line_length;
		current += cast->step_ex;
		i += 1;
	}
}

void	x_coords(t_info *info, t_casting *cast, double coords[2], double *current_distance)
{
	double	ratio;
	double	angle;

	angle = vector_angle(cast->exit_ray, cast->ray);
	if (fabs(angle) < 0.0001)
		*current_distance = cast->exit_dist;
	else
		*current_distance = cast->exit_dist / cos(angle);
	ratio = sqrt(pow(*current_distance, 2) / (pow(cast->ray[0], 2) \
				+ pow(cast->ray[1], 2)));
	coords[0] = info->player.x + cast->ray[0] * ratio;
	coords[1] = info->player.y + cast->ray[1] * ratio;
}


int	pls_help_exit(t_info *info, t_casting *cast, int i)
{
	double	coords[2];
	double	current_dist;

	x_coords(info, cast, coords, &current_dist);
	cast->percent_ex = distance(cast->exit_ends[0], cast->exit_ends[1], coords[0], coords[1]);
	if (cast->percent_ex >= 1)
		cast->percent_ex = 0.9999;
	cast->percent_ex = floor(cast->percent_ex * (double)cast->texture_ex.width);
	cast->ex_height = (distance(0, 0, cast->ray[0], cast->ray[1]) / current_dist) * ((double)info->w / 2);
	cast->start_px_ex = (int)floor((((double)info->h - 1) / 2) - \
			((double)cast->ex_height / 2));
	cast->end_px_ex = cast->start_px_ex + cast->ex_height - 1;
	cast->step_ex = ((double)1 / (double)cast->ex_height) * \
		(double)(cast->texture_ex.height);
	put_the_wall_exit(info, cast, i);
	return (0);
}

void	get_the_exit(t_info *info, t_casting *cast, int i)
{
	if (cast->exit[0] == 0 || cast->exit[1] == 0)
		return ;
	init_exit(info, cast);
	pls_help_exit(info, cast, i);
}
