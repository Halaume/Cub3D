/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_basic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:38:59 by ghanquer          #+#    #+#             */
/*   Updated: 2022/09/01 15:02:26 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_parsing_info_err(t_info *info)
{
	ft_putstr_error("Error\nSome informations are missing:");
	if (!info->texture_n.path)
		ft_putstr_error(" North texture");
	if (!info->texture_s.path)
		ft_putstr_error(" South texture");
	if (!info->texture_w.path)
		ft_putstr_error(" West texture");
	if (!info->texture_e.path)
		ft_putstr_error(" East texture");
	if (!info->color_sky)
		ft_putstr_error(" ceilling color");
	if (!info->color_floor)
		ft_putstr_error(" floor color");
	return (ft_putstr_error("\n"));
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
	my_hook.mouse_hold = 0;
	my_hook.mouse_pos = 0;
	my_hook.mouse_prev_pos = 0;
	return (my_hook);
}

void	init_texture(t_info *info)
{
	info->texture_n.img.img = NULL;
	info->texture_s.img.img = NULL;
	info->texture_e.img.img = NULL;
	info->texture_w.img.img = NULL;
	info->texture_n.path = NULL;
	info->texture_s.path = NULL;
	info->texture_e.path = NULL;
	info->texture_w.path = NULL;
}

void	init_info(t_info *info, char *file)
{
	info->h = HEIGHT;
	info->w = WIDTH;
	info->fd = 0;
	info->mlx = NULL;
	info->window = NULL;
	info->hook = init_hook();
	init_texture(info);
	info->color_sky = 0;
	info->color_floor = 0;
	info->nb_i = 0;
	info->cur_i = 0;
	info->map = NULL;
	info->mapping = NULL;
	if (ft_parse(info, file))
		exit (1);
	if (new_init_player(info))
		exit (1);
	info->nb_line = ft_tablen(info->map) - 1;
	info->nb_col = ft_strlen(info->map[0]);
}
