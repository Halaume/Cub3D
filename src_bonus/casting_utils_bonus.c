/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 16:32:49 by ghanquer          #+#    #+#             */
/*   Updated: 2022/09/05 16:34:19 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

void	restart_cast(t_info *info, t_casting *cast, int i)
{
	cast->do_exit = 0;
	cast->exit[0] = 0;
	cast->exit[1] = 0;
	cast->ray[0] = (cast->proj_screen[0] + cast->dir_v_x * i) - info->player.x;
	cast->ray[1] = (cast->proj_screen[1] + cast->dir_v_y * i) - info->player.y;
	cast->curr[0] = info->player.x;
	casting_next(info, cast);
}

void	norme_angle1(t_info *info, t_casting *cast)
{
	t_door	*door;

	cast->curr[1] = cast->delta[0] * cast->ray[1] + cast->prev_y;
	cast->side = 0;
	door = get_this_door(info->door, (int)cast->curr[0], (int)cast->curr[1]);
	if (info->map[(int)cast->curr[1]][(int)cast->curr[0]] == 'X')
	{
		cast->exit[0] = cast->curr[0];
		cast->exit[1] = cast->curr[1];
		cast->exit_ray[0] = cast->ray[0];
		cast->exit_ray[1] = cast->ray[1];
		cast->exit_state = 4;
	}
	if (info->map[(int)cast->curr[1]][(int)cast->curr[0]] == '1'
			|| is_in_corner(info, cast->curr, cast->ray, 2))
		cast->is_wall = 2;
	if (info->map[(int)cast->curr[1]][(int)cast->curr[0]] == '2' \
			&& door && door->is_op == 0)
		cast->is_wall = 4;
}

void	norme_angle2(t_info *info, t_casting *cast)
{
	t_door	*door;

	cast->curr[0] = cast->delta[1] * cast->ray[0] + cast->prev_x;
	cast->side = 1;
	door = get_this_door(info->door, (int)cast->curr[0], (int)cast->curr[1]);
	if (info->map[(int)cast->curr[1]][(int)cast->curr[0]] == 'X')
	{
		cast->exit[0] = cast->curr[0];
		cast->exit[1] = cast->curr[1];
		cast->exit_ray[0] = cast->ray[0];
		cast->exit_ray[1] = cast->ray[1];
		cast->exit_state = 3;
	}
	if (info->map[(int)cast->curr[1]][(int)cast->curr[0]] == '1' \
			|| is_in_corner(info, cast->curr, cast->ray, 1))
		cast->is_wall = 1;
	if (info->map[(int)cast->curr[1]][(int)cast->curr[0]] == '2' \
			&& door && door->is_op == 0)
		cast->is_wall = 3;
}

void	norme_droit1(t_info *info, t_casting *cast, t_door *door)
{
	if (info->map[(int)cast->curr[1]][(int)cast->curr[0]] == 'X')
	{
		cast->exit[0] = cast->curr[0];
		cast->exit[1] = cast->curr[1];
		cast->exit_ray[0] = cast->ray[0];
		cast->exit_ray[1] = cast->ray[1];
		cast->exit_state = 3;
	}
	if (info->map[(int)cast->curr[1]][(int)cast->curr[0]] == '1')
		cast->is_wall = 1;
	else if (info->map[(int)cast->curr[1]][(int)cast->curr[0]] == '2' \
			&& door && door->is_op == 0)
		cast->is_wall = 3;
	else
	{
		cast->curr[1] += 1;
		if (cast->ray[1] < 0)
			cast->curr[1] -= 2;
	}
}

void	norme_droit2(t_info *info, t_casting *cast, t_door *door)
{
	if (info->map[(int)cast->curr[1]][(int)cast->curr[0]] == 'X')
	{
		cast->exit[0] = cast->curr[0];
		cast->exit[1] = cast->curr[1];
		cast->exit_ray[0] = cast->ray[0];
		cast->exit_ray[1] = cast->ray[1];
		cast->exit_state = 4;
	}
	if (info->map[(int)cast->curr[1]][(int)cast->curr[0]] == '1')
		cast->is_wall = 2;
	else if (info->map[(int)cast->curr[1]][(int)cast->curr[0]] == '2' \
			&& door && door->is_op == 0)
		cast->is_wall = 4;
	else
	{
		cast->curr[0] += 1;
		if (cast->ray[0] < 0)
			cast->curr[0] -= 2;
	}
}
