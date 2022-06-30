/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_basic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:38:59 by ghanquer          #+#    #+#             */
/*   Updated: 2022/06/30 16:48:08 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_player	new_init_player(void)
{
	t_player	player;

	player.x = 5;
	player.y = 5;
	player.angle = M_PI / 2;
	return (player);
}

t_hooking	init_hook(void)
{
	t_hooking	my_hook;

	my_hook.forward = 0;
	my_hook.forward2 = 0;
	my_hook.backward = 0;
	my_hook.backward2 = 0;
	my_hook.left = 0;
	my_hook.right = 0;
	my_hook.cam_left = 0;
	my_hook.cam_right = 0;
	return (my_hook);
}

void	init_info(t_info *info)
{
	info->player = new_init_player();
	info->h = 1080;
	info->w = 1920;
	info->fd = 0;
	info->mlx = NULL;
	info->window = NULL;
	info->color_sky = 0x000000FF;
	info->color_floor = 0x0000FF00;
	info->nb_line = 9;
	info->nb_col = 9;
	info->hook = init_hook();
}

void	tracing_again(t_info *info)
{
	mlx_destroy_image(info->mlx, info->img.img);
	info->img.img = mlx_new_image(info->mlx, 1920, 1080);
	info->img.addr = mlx_get_data_addr(info->img.img, \
			&info->img.bits_per_pixel, &info->img.line_length, \
			&info->img.endian);
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
	mlx_destroy_display(info->mlx);
	free(info->mlx);
	free_func(info);
	exit (0);
	return (1);
}
