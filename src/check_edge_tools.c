/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_edge_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 16:58:31 by nflan             #+#    #+#             */
/*   Updated: 2022/09/05 16:58:40 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
