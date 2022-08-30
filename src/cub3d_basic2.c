/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_basic2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:03:26 by ghanquer          #+#    #+#             */
/*   Updated: 2022/08/30 18:30:50 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	tracing_again(t_info *info)
{
	info->cur_i++;
	if (info->cur_i >= NB_IMG)
		info->cur_i = 0;
	brice_casting(info);
}

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

int	closewin(t_info *info)
{
	mlx_destroy_image(info->mlx, info->img[info->cur_i].img);
	mlx_destroy_window(info->mlx, info->window);
	mlx_do_key_autorepeaton(info->mlx);
	free_func(info);
	mlx_destroy_display(info->mlx);
	free(info->mlx);
	exit (0);
}
