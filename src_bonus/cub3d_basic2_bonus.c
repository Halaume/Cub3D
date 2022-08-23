/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_basic2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:03:26 by ghanquer          #+#    #+#             */
/*   Updated: 2022/08/23 11:11:57 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	tracing_again(t_info *info)
{
	mlx_destroy_image(info->mlx, info->img.img);
	info->img.img = mlx_new_image(info->mlx, info->w, info->h);
	if (!info->img.img)
	{
		ft_closewin(info, 1);
		ft_putstr_error("Error\nImage issue\n");
		exit(1);
	}
	info->img.addr = mlx_get_data_addr(info->img.img, \
			&info->img.bits_per_pixel, &info->img.line_length, \
			&info->img.endian);
	if (!info->img.addr)
	{
		ft_closewin(info, 1);
		ft_putstr_error("Error\nImage address issue\n");
		exit(1);
	}
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
	mlx_destroy_image(info->mlx, info->img.img);
	mlx_destroy_window(info->mlx, info->window);
	mlx_do_key_autorepeaton(info->mlx);
	free_func(info);
	mlx_destroy_display(info->mlx);
	free(info->mlx);
	exit (0);
}
