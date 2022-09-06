/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_edge_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 14:28:11 by ghanquer          #+#    #+#             */
/*   Updated: 2022/09/06 15:42:44 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

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
	else if (fabs(ceil(tmp[0]) - tmp[0]) < 0.0002
		|| fabs(floor(tmp[0]) - tmp[0]) < 0.0001)
	{
		set_curr(cast, tmp[0], ceil(tmp[1]));
		if (is_on_door(info, cast))
		{
			if (check_north_corner(info, cast, tmp))
				return (3);
			return (set_curr(cast, tmp[0], ceil(tmp[1])), 3);
		}
	}
	if (is_on_door(info, cast))
		return (3);
	return (set_curr(cast, tmp[0], tmp[1]), cast->is_wall);
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
	else if (fabs(ceil(tmp[0]) - tmp[0]) < 0.0002
		|| fabs(floor(tmp[0]) - tmp[0]) < 0.0001)
	{
		set_curr(cast, tmp[0], (floor(tmp[1]) - 0.0001));
		if (is_on_door(info, cast))
		{
			if (check_south_corner(info, cast, tmp))
				return (3);
			return (set_curr(cast, tmp[0], ceil(tmp[1])), 3);
		}
	}
	if (is_on_door(info, cast))
		return (3);
	return (set_curr(cast, tmp[0], tmp[1]), cast->is_wall);
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
	else if (fabs(ceil(tmp[1]) - tmp[1]) < 0.0002
		|| fabs(floor(tmp[1]) - tmp[1]) < 0.0001)
	{
		set_curr(cast, (floor(tmp[0]) - 0.0001), tmp[1]);
		if (is_on_door(info, cast))
		{
			if (check_east_corner(info, cast, tmp))
				return (4);
			return (set_curr(cast, (floor(tmp[0]) - 0.0001), tmp[1]), 3);
		}
	}
	if (is_on_door(info, cast))
		return (4);
	return (set_curr(cast, tmp[0], tmp[1]), cast->is_wall);
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
	else if (fabs(ceil(tmp[1]) - tmp[1]) < 0.0002
		|| fabs(floor(tmp[1]) - tmp[1]) < 0.0001)
	{
		set_curr(cast, ceil(tmp[0]), tmp[1]);
		if (is_on_door(info, cast))
		{
			if (check_west_corner(info, cast, tmp))
				return (4);
			return (set_curr(cast, ceil(tmp[0]), tmp[1]), 3);
		}
	}
	if (is_on_door(info, cast))
		return (4);
	return (set_curr(cast, tmp[0], tmp[1]), cast->is_wall);
}
