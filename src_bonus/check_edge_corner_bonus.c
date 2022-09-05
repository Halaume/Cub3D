/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_edge_corner_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:07:38 by ghanquer          #+#    #+#             */
/*   Updated: 2022/09/05 18:03:27 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

int	is_on_door(t_info *info, t_casting *cast)
{
	t_door	*door;

	door = get_this_door(info->door, (int)cast->curr[0], (int)cast->curr[1]);
	if (door && !door->is_op)
		return (1);
	return (0);
}

int	check_north_corner(t_info *info, t_casting *cast, double tmp[2])
{
	if ((cast->ray[0] <= 0 && info->map[(int)(tmp[1])]
		[(int)(tmp[0] + 1)] == '1') || (cast->ray[0] >= 0
			&& info->map[(int)(tmp[1])][(int)(tmp[0] - 1)] == '1'))
	{
		cast->curr[0] = 0.9999;
		if (cast->ray[0] <= 0)
			cast->curr[0] = 0;
		cast->curr[1] = 0.9999;
		return (1);
	}
	if (cast->ray[0] <= 0)
	{
		cast->curr[1] = tmp[1];
		cast->curr[0] = floor(tmp[0] + 1);
		if (is_on_door(info, cast))
			return (3);
	}
	else
	{
		cast->curr[1] = tmp[1];
		cast->curr[0] = floor(tmp[0]) - 0.0001;
		if (is_on_door(info, cast))
			return (3);
	}
	return (0);
}

int	check_south_corner(t_info *info, t_casting *cast, double tmp[2])
{
	if ((cast->ray[0] <= 0 && info->map[(int)(tmp[1])]
		[(int)(tmp[0] + 1)] == '1') || (cast->ray[0] >= 0
			&& info->map[(int)(tmp[1])][(int)(tmp[0] - 1)] == '1'))
	{
		cast->curr[0] = 0.9999;
		if (cast->ray[0] <= 0)
			cast->curr[0] = 0;
		cast->curr[1] = 0;
		return (1);
	}
	if (cast->ray[0] <= 0)
	{
		cast->curr[0] = floor(tmp[0] + 1);
		cast->curr[1] = tmp[1];
		if (is_on_door(info, cast))
			return (3);
	}
	else
	{
		cast->curr[0] = floor(tmp[0]) - 0.0001;
		cast->curr[1] = tmp[1];
		if (is_on_door(info, cast))
			return (3);
	}
	return (0);
}

int	check_west_corner(t_info *info, t_casting *cast, double tmp[2])
{
	if ((cast->ray[1] <= 0 && info->map[(int)(tmp[1] + 1)]
		[(int)(tmp[0])] == '1') || (cast->ray[1] >= 0
			&& info->map[(int)(tmp[1] - 1)][(int)(tmp[0])] == '1'))
	{
		cast->curr[1] = 0.9999;
		if (cast->ray[1] <= 0)
			cast->curr[1] = 0;
		cast->curr[0] = 0.9999;
		return (2);
	}
	if (cast->ray[1] <= 0)
	{
		cast->curr[0] = tmp[0];
		cast->curr[1] = floor(tmp[1] + 1);
		if (is_on_door(info, cast))
			return (4);
	}
	else
	{
		cast->curr[0] = tmp[0];
		cast->curr[1] = floor(tmp[1]) - 0.0001;
		if (is_on_door(info, cast))
			return (4);
	}
	return (0);
}

int	check_east_corner(t_info *info, t_casting *cast, double tmp[2])
{
	if ((cast->ray[1] <= 0 && info->map[(int)(tmp[1] + 1)]
		[(int)(tmp[0])] == '1') || (cast->ray[1] >= 0
			&& info->map[(int)(tmp[1] - 1)][(int)(tmp[0])] == '1'))
	{
		cast->curr[1] = 0.9999;
		if (cast->ray[1] <= 0)
			cast->curr[1] = 0;
		cast->curr[0] = 0;
		return (2);
	}
	if (cast->ray[1] <= 0)
	{
		cast->curr[0] = tmp[0];
		cast->curr[1] = floor(tmp[1] + 1);
		if (is_on_door(info, cast))
			return (4);
	}
	else
	{
		cast->curr[0] = tmp[0];
		cast->curr[1] = floor(tmp[1]) - 0.0001;
		if (is_on_door(info, cast))
			return (4);
	}
	return (0);
}
