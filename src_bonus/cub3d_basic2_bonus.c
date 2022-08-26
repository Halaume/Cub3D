/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_basic2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:03:26 by ghanquer          #+#    #+#             */
/*   Updated: 2022/08/26 17:04:04 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

void	ft_next_texture(t_info *info)
{
	if (info->texture_n->next)
		info->texture_n = info->texture_n->next;
	if (info->texture_s->next)
		info->texture_s = info->texture_s->next;
	if (info->texture_e->next)
		info->texture_e = info->texture_e->next;
	if (info->texture_w->next)
		info->texture_w = info->texture_w->next;
	if (info->texture_d && info->texture_d->next)
		info->texture_d = info->texture_d->next;
	if (info->texture_ex && info->texture_ex->next)
		info->texture_ex = info->texture_ex->next;
}

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
	door_closed(info);
	ft_next_texture(info);
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
	ft_free(info);
	mlx_destroy_display(info->mlx);
	free(info->mlx);
	exit (0);
}
