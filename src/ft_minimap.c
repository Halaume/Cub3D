/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 11:21:16 by nflan             #+#    #+#             */
/*   Updated: 2022/08/18 15:29:21 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_init_color_minimap(t_info *info, int pos[2], int rgb[3])
{
	int	px;
	int	py;

	px = (int) info->player.x + pos[0];
	py = (int) info->player.y + pos[1];
	if (px < 0 || px >= info->nb_col || py < 0 || py >= info->nb_line)
		ft_space_color(rgb);
	else if (px == (int) info->player.x && py == (int) info->player.y)
		ft_player_color(rgb);
	else if (info->map[py][px] == ' ')
		ft_space_color(rgb);
	else if (info->map[py][px] == '1')
		ft_wall_color(rgb);
	else if (info->map[py][px] == '2')
		ft_door_color(rgb);
	else
		ft_floor_color(rgb);
}

int	ft_fill_minimap(t_info *info, int x, int y, int pos[2])
{
	int	i;
	int	j;
	int	rgb[3];

	i = -1;
	ft_init_color_minimap(info, pos, rgb);
	while (++i < 20)
	{
		j = -1;
		while (++j < 20)
		{
			if ((y == 10 && i == 0) || (x == info->w - 190 && j == 0)
				|| (x == info->w - 30 && j == 19) || (y == 170 && i == 19))
				my_mlx_pixel_put(&info->img, x + j, y + i,
					create_trgb(100, 0, 0, 0));
			else
				my_mlx_pixel_put(&info->img, x + j, y + i,
					create_trgb(100, rgb[0], rgb[1], rgb[2]));
		}
	}
	return (0);
}

int	ft_launch_minimap(t_info *info)
{
	int	x;
	int	y;
	int	pos[2];

	pos[1] = -4;
	y = 10;
	while (y < 190)
	{
		pos[0] = -4;
		x = info->w - 190;
		while (x < info->w - 10)
		{
			ft_fill_minimap(info, x, y, pos);
			x += 20;
			pos[0] += 1;
		}
		y += 20;
		pos[1] += 1;
	}
	return (0);
}

void	ft_mapping(t_info *info)
{
	if (!info->print_map)
		ft_launch_minimap(info);
	else if (info->print_map)
		ft_draw_map(info);
}
