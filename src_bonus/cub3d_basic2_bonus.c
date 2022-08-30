/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_basic2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:03:26 by ghanquer          #+#    #+#             */
/*   Updated: 2022/08/30 16:49:57 by nflan            ###   ########.fr       */
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
	info->cur_i++;
	if (info->cur_i >= NB_IMG)
		info->cur_i = 0;
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

/*int	closewin(t_info *info)
{
	mlx_destroy_image(info->mlx, info->img[info->cur_i].img);
	mlx_destroy_window(info->mlx, info->window);
	ft_free(info);
	mlx_do_key_autorepeaton(info->mlx);
	mlx_destroy_display(info->mlx);
	free(info->mlx);
	exit (0);
}*/
