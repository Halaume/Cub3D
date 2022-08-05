/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 10:43:10 by ghanquer          #+#    #+#             */
/*   Updated: 2022/08/05 17:49:05 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	is_wall(t_info *info, double y, double x)
{
	if ((int)y > info->nb_line || (int)x > info->nb_col || (int)x < 0
		|| (int)y < 0)
		return (1);
	if (info->map[(int)y][(int)x] == '1')
		return (1);
	return (0);
}

void	turn_right(t_info *info)
{
	info->player.angle -= ((5 * M_PI) / 180);
	if (info->player.angle == 2 * M_PI)
		info->player.angle = 0;
}

void	turn_left(t_info *info)
{
	info->player.angle += ((5 * M_PI) / 180);
	if (info->player.angle == 2 * M_PI)
		info->player.angle = 0;
}
