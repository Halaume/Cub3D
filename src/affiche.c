/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affiche.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:08:55 by ghanquer          #+#    #+#             */
/*   Updated: 2022/06/30 17:02:29 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	put_col(t_info *info, int start_px, int end_px, int y, double percent, double wall_height)
{
//	int	color_wall;
	int	i;

	(void)percent;
	double	step;
	char *dist = info->img.addr + y * (info->img.bits_per_pixel / 8);
	char *origin = info->texture.img.addr + (int)percent * (info->texture.img.bits_per_pixel / 8);
	step = ((double)1 / (double)wall_height) * (double)(info->texture.height);

//	color_wall = 0x00FF0000;
	i = 0;
//	printf("start pixel = %d\n", start_px);
	while (i < start_px)
	{
		*(unsigned int *)dist = info->color_sky;
		dist += info->img.line_length;
//		my_mlx_pixel_put(&info->img, y, i, info->color_sky);
		i++;
	}
	double current = (double)(i - start_px) * step;
	int	percent_y = (int)current;
	while (i < end_px && i < info->h)
	{
		percent_y = (int)current;
		if (percent_y == info->texture.height) //texture.height
			percent_y = info->texture.height - 1; //texture.height
		*(unsigned int *)dist = *(unsigned int *)(origin + (int)percent_y * info->texture.img.line_length); //texture.line_length
		dist += info->img.line_length;
		current += step;
		i++;
	}
	while (i < info->h)
	{
		*(unsigned int *)dist = info->color_floor;
		dist += info->img.line_length;
//		my_mlx_pixel_put(&info->img, y, i, info->color_floor);
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
