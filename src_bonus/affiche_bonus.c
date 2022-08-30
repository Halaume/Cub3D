/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affiche_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:08:55 by ghanquer          #+#    #+#             */
/*   Updated: 2022/08/30 15:15:04 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

void	put_the_wall(t_info *info, t_casting *cast, int *i)
{
	cast->current = (double)(*i - cast->start_px) * cast->step;
	cast->percent_y = (int)cast->current;
	while (*i < cast->end_px && *i < info->h)
	{
		cast->percent_y = (int)cast->current;
		if (cast->percent_y == cast->texture.height)
			cast->percent_y = cast->texture.height - 1;
		*(unsigned int *)cast->dist = *(unsigned int *)(cast->origin + \
				(int)cast->percent_y * cast->texture.img.line_length);
		cast->dist += info->img[info->cur_i].line_length;
		cast->current += cast->step;
		*i += 1;
	}
}

void	put_col(t_info *info, t_casting *cast, int y)
{
	int		i;

	cast->dist = info->img[info->cur_i].addr + y * (info->img[info->cur_i].bits_per_pixel / 8);
	cast->origin = cast->texture.img.addr + (int)cast->percent * \
				(cast->texture.img.bits_per_pixel / 8);
	cast->step = ((double)1 / (double)cast->wall_height) * \
		(double)(cast->texture.height);
	i = 0;
	while (i < cast->start_px)
	{
		*(unsigned int *)cast->dist = info->color_sky;
		cast->dist += info->img[info->cur_i].line_length;
		i++;
	}
	put_the_wall(info, cast, &i);
	while (i < info->h)
	{
		*(unsigned int *)cast->dist = info->color_floor;
		cast->dist += info->img[info->cur_i].line_length;
		i++;
	}
}
