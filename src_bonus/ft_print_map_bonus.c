/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_map_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 11:21:07 by nflan             #+#    #+#             */
/*   Updated: 2022/08/30 15:16:49 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

int	ft_print_map(t_info *info, int x, int y, int rgb[3])
{
	int	i;
	int	j;
	int	diff;

	i = -1;
	diff = -10;
	if (info->nb_col > 94 || info->nb_line > 52)
		diff = info->s_m;
	while (++i < info->s_m)
	{
		j = -1;
		while (++j < info->s_m)
		{
			if ((y == 10 && i == 0) || (x == 10 && j == 0)
				|| (y == info->nb_line * info->s_m + diff && i == info->s_m - 1)
				|| (x == info->nb_col * info->s_m + diff && j == info->s_m - 1))
				my_mlx_pixel_put(&info->img[info->cur_i], x + j, y + i,
					create_trgb(100, 0, 0, 0));
			else
				my_mlx_pixel_put(&info->img[info->cur_i], x + j, y + i, create_trgb(100,
						rgb[0], rgb[1], rgb[2]));
		}
	}
	return (0);
}

void	ft_init_color_map(t_info *info, int ij[2], int rgb[3])
{
	if (ij[1] == (int) info->player.x && ij[0] == (int) info->player.y)
		ft_player_color(rgb);
	else if (info->map[ij[0]][ij[1]] == ' ')
		ft_space_color(rgb);
	else if (info->map[ij[0]][ij[1]] == '1')
		ft_wall_color(rgb);
	else if (info->map[ij[0]][ij[1]] == '2')
		ft_door_color(rgb);
	else if (info->map[ij[0]][ij[1]] == 'X')
		ft_exit_color(rgb);
	else
		ft_floor_color(rgb);
}

void	ft_draw_map(t_info *info)
{
	int	x;
	int	y;
	int	ij[2];
	int	rgb[3];

	ij[0] = 0;
	y = 10;
	while (info->map[ij[0]])
	{
		ij[1] = 0;
		x = 10;
		while (info->map[ij[0]][ij[1]])
		{
			ft_init_color_map(info, ij, rgb);
			ft_print_map(info, x, y, rgb);
			x += info->s_m;
			ij[1] += 1;
		}
		y += info->s_m;
		ij[0] += 1;
	}
}

void	ft_map(t_info *info)
{
	if (!info->print_map)
		info->print_map = 1;
	else
		info->print_map = 0;
}
