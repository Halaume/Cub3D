/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affiche.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:08:55 by ghanquer          #+#    #+#             */
/*   Updated: 2022/06/25 15:11:15 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	put_col(t_info *info, int start_px, int end_px, int y, int percent, double wall_height)
{
//	int	color_wall;
	int	i;


	double step;
	char *dist;
	char *origin = info->img.addr + (int)percent * (info->img.bits_per_pixel / 8);
	step = ((double)1 / (double)wall_height) * 128/* * (double)(texture.height)*/;


//	color_wall = 0x00FF0000;
	i = 0;
	double current = (double)i - start_px * step;
	int	percent_y = (int)current;
	while (i < start_px)
	{
		my_mlx_pixel_put(&info->img, y, i, info->color_sky);
		i++;
	}
	while (i < end_px && i < info->h)
	{
		*(unsigned int *)dist = *(unsigned int *)(origin + (int)percent_y * info->img.line_length);
	dist += info->img.line_length;
	current += step;
		i++;
	}
	while (i < info->h)
	{
		my_mlx_pixel_put(&info->img, y, i, info->color_floor);
		i++;
	}
}

/*
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < WIDTH && y < HEIGHT && x > 0 && y > 0)
	{
		dst = data->addr + \
			(y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}
*/
