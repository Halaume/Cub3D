/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_basic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:38:59 by ghanquer          #+#    #+#             */
/*   Updated: 2022/08/03 17:17:38 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	new_init_player(t_info *info)
{
	int			x;
	int			y;
	char		**tab;

	tab = info->map;
	y = 0;
	while (tab[y])
	{
		x = 0;
		while (tab[y][x] && (tab[y][x] != 'W' && tab[y][x] != 'N' && tab[y][x] != 'S' && tab[y][x] != 'E'))
			x++;
		if (tab[y][x])
			break ;
		y++;
	}
	if (!tab[y])
		return (free_func(info), ft_putstr_error("Error\nJoueur introuvable\n"));
	info->player.x = x;
	info->player.y = y;
	if (tab[y][x] == 'N')
		info->player.angle = M_PI / 2;
	else if (tab[y][x] == 'S')
		info->player.angle = M_PI * 1.5;
	else if (tab[y][x] == 'W')
		info->player.angle = M_PI;
	else if (tab[y][x] == 'E')
		info->player.angle = M_PI * 2;
	return (0);
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

void	init_info(t_info *info, char *file)
{
	info->h = 1080;
	info->w = 1920;
	info->fd = 0;
	info->mlx = NULL;
	info->window = NULL;
	info->hook = init_hook();
	info->texture_n.img.img = NULL;
	info->texture_s.img.img = NULL;
	info->texture_e.img.img = NULL;
	info->texture_w.img.img = NULL;
	info->texture_n.path = NULL;
	info->texture_s.path = NULL;
	info->texture_e.path = NULL;
	info->texture_w.path = NULL;
	info->img.img = NULL;
	info->img.addr = NULL;
	info->map = NULL;
	info->mapping = NULL;
	if (ft_parse(info, file))
		exit (1);
	if (new_init_player(info))
		exit (1);
	info->nb_line = ft_tablen(info->map);
	info->nb_col = ft_longest(info->mapping);
}
