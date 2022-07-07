/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_basic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:38:59 by ghanquer          #+#    #+#             */
/*   Updated: 2022/07/07 14:03:55 by ghanquer         ###   ########.fr       */
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
	info->texture_n.img.img = NULL;
	info->texture_s.img.img = NULL;
	info->texture_e.img.img = NULL;
	info->texture_w.img.img = NULL;
	info->texture_n.path = NULL;
	info->texture_s.path = NULL;
	info->texture_e.path = NULL;
	info->texture_w.path = NULL;
}
