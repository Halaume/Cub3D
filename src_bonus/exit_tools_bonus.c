/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_tools_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 16:44:17 by ghanquer          #+#    #+#             */
/*   Updated: 2022/09/05 16:44:42 by ghanquer         ###   ########.fr       */
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

void	init_exit(t_info *info, t_casting *cast)
{
	double	ratio;

	cast->texture_ex = *info->texture_ex;
	cast->curr[0] = cast->exit[0];
	cast->curr[1] = cast->exit[1];
	cast->ray[0] = cast->exit_ray[0];
	cast->ray[1] = cast->exit_ray[1];
	cast->exit_mid[0] = floor(cast->curr[0]) + 0.5;
	cast->exit_mid[1] = floor(cast->curr[1]) + 0.5;
	cast->exit_dist = distance(info->player.x, info->player.y,
			cast->exit_mid[0], cast->exit_mid[1]);
	cast->exit_ray[0] = -(cast->exit_mid[1] - info->player.y);
	cast->exit_ray[1] = cast->exit_mid[0] - info->player.x;
	ratio = sqrt(pow(0.5, 2) / (pow(cast->exit_ray[0], 2)
				+ pow(cast->exit_ray[1], 2)));
	cast->exit_ends[0] = ratio * cast->exit_ray[0] + cast->exit_mid[0];
	cast->exit_ends[1] = ratio * cast->exit_ray[1] + cast->exit_mid[1];
	cast->exit_ends[2] = -ratio * cast->exit_ray[0] + cast->exit_mid[0];
	cast->exit_ends[3] = -ratio * cast->exit_ray[1] + cast->exit_mid[1];
	cast->exit_ray[0] = cast->exit_mid[0] - info->player.x;
	cast->exit_ray[1] = cast->exit_mid[1] - info->player.y;
}
