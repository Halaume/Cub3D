/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brice_casting_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:37:14 by ghanquer          #+#    #+#             */
/*   Updated: 2022/09/06 12:33:18 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

int	is_in_corner(t_info *info, double curr[2], double ray[2], int hit)
{
	int		c[2];

	c[0] = (int)curr[0];
	c[1] = (int)curr[1];
	if (hit == 1)
	{
		if (ray[1] < 0 && info->map[(c[1] + 1)][c[0]] == '1'
			&& ((ray[0] <= 0 && info->map[c[1]][(c[0] + 1)] == '1')
				|| (ray[0] >= 0 && info->map[c[1]][(c[0] - 1)] == '1')))
			return (1);
		else if (ray[1] > 0 && info->map[(c[1] - 1)][c[0]] == '1'
			&& ((ray[0] <= 0 && info->map[c[1]][(c[0] + 1)] == '1')
				|| (ray[0] >= 0 && info->map[c[1]][(c[0] - 1)] == '1')))
			return (1);
		return (0);
	}
	if (ray[0] < 0 && info->map[c[1]][(c[0] + 1)] == '1'
		&& ((ray[1] <= 0 && info->map[(c[1] + 1)][c[0]] == '1')
			|| (ray[1] >= 0 && info->map[(c[1] - 1)][c[0]] == '1')))
		return (1);
	else if (ray[0] > 0 && info->map[c[1]][(c[0] - 1)] == '1'
		&& ((ray[1] <= 0 && info->map[(c[1] + 1)][c[0]] == '1')
			|| (ray[1] >= 0 && info->map[(c[1] - 1)][c[0]] == '1')))
		return (1);
	return (0);
}

void	cast_droit(t_info *info, t_casting *cast)
{
	t_door	*door;

	door = get_this_door(info->door, (int)cast->curr[0], (int)cast->curr[1]);
	if (fabs(cast->ray[0]) < 0.0001)
		norme_droit1(info, cast, door);
	else
		norme_droit2(info, cast, door);
}

void	cast_angle(t_info *info, t_casting *cast)
{
	if (fabs(cast->delta[0] - cast->delta[1]) < 0.0001 || \
			cast->delta[0] < cast->delta[1])
		norme_angle1(info, cast);
	else
		norme_angle2(info, cast);
	if (cast->is_wall == 0)
	{
		cast->prev_x = cast->curr[0];
		cast->prev_y = cast->curr[1];
		next_curr(cast, cast->side);
	}
}

void	casting_next(t_info *info, t_casting *cast)
{
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
		restart_cast(info, &cast, i);
		while (cast.is_wall == 0)
		{
			if (fabs(cast.ray[0]) < 0.0001 || fabs(cast.ray[1]) < 0.0001)
				cast_droit(info, &cast);
			else
				cast_angle(info, &cast);
		}
		get_the_wall(info, &cast, i);
	}
	ft_mapping(info);
}
