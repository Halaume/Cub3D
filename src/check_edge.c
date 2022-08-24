/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_edge.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 14:28:11 by ghanquer          #+#    #+#             */
/*   Updated: 2022/08/23 17:08:26 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	check_north(t_info *info, t_casting *cast)
{
	if (info->map[(int)(cast->curr[1] + 1)][(int)cast->curr[0]] == '1')
	{
		cast->is_wall = 2;
		if ((cast->ray[0] <= 0 && info->map[(int)(cast->curr[1] + 1)] \
					[(int)cast->curr[0]] == '1') || (cast->ray[0] >= 0 && \
					info->map[(int)(cast->curr[1] - 1)][(int)cast->curr[0]] \
					== '1'))
		{
			cast->is_wall = 1;
			if (cast->ray[0] <= 0)
				cast->curr[0] = 0;
			else
				cast->curr[0] = 0.9999;
			cast->curr[1] = 0.9999;
		}
	}
}

void	check_south(t_info *info, t_casting *cast)
{
	if (info->map[(int)(cast->curr[1] - 1)][(int)cast->curr[0]] == '1')
	{
		cast->is_wall = 2;
		if ((cast->ray[0] <= 0 && info->map[(int)(cast->curr[1] + 1)] \
					[(int)cast->curr[0]] == '1') || (cast->ray[0] >= 0 && \
					info->map[(int)(cast->curr[1] - 1)][(int)cast->curr[0]] \
					== '1'))
		{
			cast->is_wall = 1;
			if (cast->ray[0] <= 0)
				cast->curr[0] = 0;
			else
				cast->curr[0] = 0.9999;
			cast->curr[1] = 0;
		}
	}
}

void	check_east(t_info *info, t_casting *cast)
{
	if (info->map[(int)cast->curr[1]][(int)(cast->curr[0] - 1)] == '1')
	{
		cast->is_wall = 1;
		if ((cast->ray[1] <= 0 && info->map[(int)(cast->curr[1] + 1)] \
					[(int)cast->curr[0]] == '1') || \
				(info->map[(int)(cast->curr[1] - 1)] \
				[(int)cast->curr[0]] == '1' && cast->ray[1] >= 0))
		{
			cast->is_wall = 2;
			if (cast->ray[1] <= 0)
				cast->curr[1] = 0;
			else
				cast->curr[1] = 0.9999;
			cast->curr[0] = 0;
		}
	}
}

void	check_west(t_info *info, t_casting *cast)
{
	if (info->map[(int)cast->curr[1]][(int)(cast->curr[0] + 1)] == '1')
	{
		cast->is_wall = 1;
		if ((cast->ray[1] <= 0 && info->map[(int)(cast->curr[1] + 1)] \
					[(int)cast->curr[0]] == '1') || (cast->ray[1] >= 0 && \
					info->map[(int)(cast->curr[1] - 1)][(int)cast->curr[0]] \
					== '1'))
		{
			cast->is_wall = 2;
			if (cast->ray[1] <= 0)
				cast->curr[1] = 0;
			else
				cast->curr[1] = 0.9999;
			cast->curr[0] = 0.9999;
		}
	}
}

void	check_angle(t_info *info, t_casting *cast)
{
	if (cast->is_wall == 1)
	{
		if (cast->ray[1] < 0)
			check_north(info, cast);
		else
			check_south(info, cast);
	}
	else
	{
		if (cast->ray[0] < 0)
			check_west(info, cast);
		else
			check_east(info, cast);
	}
}
