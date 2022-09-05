/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_basic_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:38:59 by ghanquer          #+#    #+#             */
/*   Updated: 2022/08/30 18:11:04 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

int	ft_parsing_info_err(t_info *info)
{
	ft_putstr_error("Error\nSome informations are missing:");
	if (!info->texture_n)
		ft_putstr_error(" North texture");
	if (!info->texture_s)
		ft_putstr_error(" South texture");
	if (!info->texture_w)
		ft_putstr_error(" West texture");
	if (!info->texture_e)
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
	info->texture_n = NULL;
	info->texture_s = NULL;
	info->texture_e = NULL;
	info->texture_w = NULL;
	info->texture_d = NULL;
	info->texture_ex = NULL;
}

void	ft_define_sm(t_info *info)
{
	info->s_m = 20;
	if (info->nb_col > 94 || info->nb_line > 52)
	{
		if (info->nb_col - 94 > info->nb_line - 52)
			info->s_m = info->w / info->nb_col - 1;
		else
			info->s_m = info->h / info->nb_line - 1;
	}
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
	info->map = NULL;
	info->mapping = NULL;
	info->print_map = 0;
	info->is_exit = 0;
	info->door = NULL;
	info->cur_i = 0;
	info->nb_i = 0;
	gettimeofday(&info->start, NULL);
	if (ft_parse(info, file))
		exit (1);
	if (new_init_player(info))
		exit (1);
	info->nb_line = ft_tablen(info->map);
	info->nb_col = ft_strlen(info->map[0]);
	ft_define_sm(info);
}
