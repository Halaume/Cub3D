/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_basic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:38:59 by ghanquer          #+#    #+#             */
/*   Updated: 2022/08/02 17:51:56 by nflan            ###   ########.fr       */
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

int	ft_parsarg(t_info *info)
{
	char	*buf;

	(void)info;
	buf = get_next_line(info->fd);
	if (!buf)
		return (1);
	while (buf)
	{
		ft_play(info, buf);
		free(buf);
		buf = get_next_line(info->fd);
	}
	return (0);
}

int	ft_parse(t_info *info, char *file)
{
	info->fd = open(file, O_RDONLY);
	if (info->fd == -1)
		return (ft_perror("Error\nOuverture de map echouee", NULL));
	if (ft_parsarg(info))
		return (ft_free(info), ft_putstr_error("Error\nMalloc error\n"));
	close(info->fd);
	info->fd = 0;
	return (0);
}

void	init_info(t_info *info, char *file)
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
	info->img.img = NULL;
	info->img.addr = NULL;
	info->map = NULL;
	if (ft_parse(info, file))
		exit (1);
}
