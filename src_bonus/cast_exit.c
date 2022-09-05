/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:12:32 by ghanquer          #+#    #+#             */
/*   Updated: 2022/09/05 16:44:45 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

int	put_col_exit(t_info *info, t_casting *cast, int y, double *curr)
{
	int	i;

	cast->dist = info->img[info->cur_i].addr + y
		* (info->img[info->cur_i].bits_per_pixel / 8);
	cast->origin = cast->texture_ex.img.addr + (int)cast->percent_ex * \
				(cast->texture_ex.img.bits_per_pixel / 8);
	if (cast->start_px_ex < 0)
	{
		i = 0;
		*curr = (double)(i - cast->start_px_ex) * cast->step_ex;
	}
	else
	{
		i = cast->start_px_ex;
		*curr = 0;
	}
	cast->dist += info->img[info->cur_i].line_length * i;
	return (i);
}

void	put_the_wall_exit(t_info *info, t_casting *cast, int y)
{
	int				i;
	int				percent_y;
	unsigned int	tmp;
	double			current;

	i = put_col_exit(info, cast, y, &current);
	while (i < cast->end_px_ex && i < info->h)
	{
		percent_y = (int)current;
		if (percent_y == cast->texture_ex.height)
			percent_y = cast->texture_ex.height - 1;
		tmp = *(unsigned int *)(cast->origin + \
				(int)percent_y * cast->texture_ex.img.line_length);
		if (!(tmp >> 24))
			*(unsigned int *)cast->dist = tmp;
		cast->dist += info->img[info->cur_i].line_length;
		current += cast->step_ex;
		i += 1;
	}
}

void	x_coords(t_info *info, t_casting *cast, double coords[2],
		double *current_distance)
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

int	pls_help_exit(t_info *info, t_casting *cast)
{
	double	coords[2];
	double	current_dist;

	x_coords(info, cast, coords, &current_dist);
	if (distance(coords[0], coords[1], cast->exit_mid[0],
			cast->exit_mid[1]) > 0.5)
		return (1);
	cast->do_exit = 1;
	cast->percent_ex = distance(cast->exit_ends[2], cast->exit_ends[3],
			coords[0], coords[1]);
	if (cast->percent_ex >= 1)
		cast->percent_ex = 0.9999;
	cast->percent_ex = floor(cast->percent_ex * (double)cast->texture_ex.width);
	cast->ex_height = (distance(0, 0, cast->ray[0], cast->ray[1])
			/ current_dist) * ((double)info->w / 2);
	cast->start_px_ex = (int)floor((((double)info->h - 1) / 2) - \
			((double)cast->ex_height / 2));
	cast->end_px_ex = cast->start_px_ex + cast->ex_height - 1;
	cast->step_ex = ((double)1 / (double)cast->ex_height) * \
		(double)(cast->texture_ex.height);
	return (0);
}

void	get_the_exit(t_info *info, t_casting *cast)
{
	if (cast->exit[0] == 0 || cast->exit[1] == 0)
		return ;
	init_exit(info, cast);
	pls_help_exit(info, cast);
}
