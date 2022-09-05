/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_edge.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 14:28:11 by ghanquer          #+#    #+#             */
/*   Updated: 2022/09/05 12:12:31 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	set_curr(t_casting *cast, double x, double y)
{
	cast->curr[0] = x;
	cast->curr[1] = y;
}

int	check_north(t_info *info, t_casting *cast)
{
	double	tmp[2];

	tmp[0] = cast->curr[0];
	tmp[1] = cast->curr[1];
	if (info->map[(int)(cast->curr[1] + 1)][(int)cast->curr[0]] == '1')
	{
		if (check_north_corner(info, cast, tmp))
			return (check_north_corner(info, cast, tmp));
		return (set_curr(cast, tmp[0], ceil(tmp[1])), 2);
	}
	else if (fabs(ceil(tmp[0]) - tmp[0]) < 0.0002 || fabs(floor(tmp[0]) - tmp[0]) < 0.0001)
		set_curr(cast, tmp[0], ceil(tmp[1]));
	return (set_curr(cast, tmp[0], tmp[1]), 1);
}

int	check_south(t_info *info, t_casting *cast)
{
	double	tmp[2];

	tmp[0] = cast->curr[0];
	tmp[1] = cast->curr[1];
	if (info->map[(int)(cast->curr[1] - 1)][(int)cast->curr[0]] == '1')
	{
		if (check_south_corner(info, cast, tmp))
			return (check_south_corner(info, cast, tmp));
		return (set_curr(cast, tmp[0], (floor(tmp[1]) - 0.0001)), 2);
	}
	else if (fabs(ceil(tmp[0]) - tmp[0]) < 0.0002 || fabs(floor(tmp[0]) - tmp[0]) < 0.0001)
		set_curr(cast, tmp[0], (floor(tmp[1]) - 0.0001));
	return (set_curr(cast, tmp[0], tmp[1]), 1);
}

int	check_east(t_info *info, t_casting *cast)
{
	double	tmp[2];

	tmp[0] = cast->curr[0];
	tmp[1] = cast->curr[1];
	if (info->map[(int)cast->curr[1]][(int)(cast->curr[0] - 1)] == '1')
	{
		if (check_east_corner(info, cast, tmp))
			return (check_east_corner(info, cast, tmp));
		return (set_curr(cast, (floor(tmp[0]) - 0.0001), tmp[1]), 1);
	}
	else if (fabs(ceil(tmp[1]) - tmp[1]) < 0.0002 || fabs(floor(tmp[1]) - tmp[1]) < 0.0001)
		set_curr(cast, (floor(tmp[0]) - 0.0001), tmp[1]);
	return (set_curr(cast, tmp[0], tmp[1]), 2);
}

int	check_west(t_info *info, t_casting *cast)
{
	double	tmp[2];

	tmp[0] = cast->curr[0];
	tmp[1] = cast->curr[1];
	if (info->map[(int)cast->curr[1]][(int)(cast->curr[0] + 1)] == '1')
	{
		if (check_west_corner(info, cast, tmp))
			return (check_west_corner(info, cast, tmp));
		return (set_curr(cast, ceil(tmp[0]), tmp[1]), 1);
	}
	else if (fabs(ceil(tmp[1]) - tmp[1]) < 0.0002 || fabs(floor(tmp[1]) - tmp[1]) < 0.0001)
		set_curr(cast, ceil(tmp[0]), tmp[1]);
	return (set_curr(cast, tmp[0], tmp[1]), 2);
}

void	check_angle(t_info *info, t_casting *cast)
{
	if (cast->is_wall == 1 || cast->is_wall == 3)
	{
		if (cast->ray[1] < 0)
			cast->is_wall = check_north(info, cast);
		else
			cast->is_wall = check_south(info, cast);
	}
	else
	{
		if (cast->ray[0] < 0)
			cast->is_wall = check_west(info, cast);
		else
			cast->is_wall = check_east(info, cast);
	}
}
