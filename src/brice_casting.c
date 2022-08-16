/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brice_casting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:37:14 by ghanquer          #+#    #+#             */
/*   Updated: 2022/07/07 17:33:32 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	cast_droit(t_info *info, t_casting *cast)
{
	if (fabs(cast->ray[0]) < 0.0001)
	{
		if (info->map[(int)cast->curr[1]][(int)cast->curr[0]] == '1')
			cast->is_wall = 1;
		else
		{
			cast->curr[1] += 1;
			if (cast->ray[1] < 0)
				cast->curr[1] -= 2;
		}
	}
	else
	{
		if (info->map[(int)cast->curr[1]][(int)cast->curr[0]] == '1')
			cast->is_wall = 2;
		else
		{
			cast->curr[0] += 1;
			if (cast->ray[0] < 0)
				cast->curr[0] -= 2;
		}
	}
}

void	cast_angle(t_info *info, t_casting *cast)
{
	if (fabs(cast->delta[0] - cast->delta[1]) < 0.0001 || \
			cast->delta[0] < cast->delta[1])
	{
		cast->curr[1] = cast->delta[0] * cast->ray[1] + cast->prev_y;
		cast->side = 0;
		if (info->map[(int)cast->curr[1]][(int)cast->curr[0]] == '1')
			cast->is_wall = 2;
	}
	else
	{
		cast->curr[0] = cast->delta[1] * cast->ray[0] + cast->prev_x;
		cast->side = 1;
		if (info->map[(int)cast->curr[1]][(int)cast->curr[0]] == '1')
			cast->is_wall = 1;
	}
	if (cast->is_wall == 0)
	{
		cast->prev_x = cast->curr[0];
		cast->prev_y = cast->curr[1];
		next_curr(cast, cast->side);
	}
}

void	casting2(t_info *info, t_casting *cast, int i)
{
	cast->ray[0] = (cast->proj_screen[0] + cast->dir_v_x * i) - info->player.x;
	cast->ray[1] = (cast->proj_screen[1] + cast->dir_v_y * i) - info->player.y;
	cast->curr[0] = info->player.x;
	if (fabs(cast->ray[0]) > 0.0001)
	{
		if (cast->ray[0] < -0.0001)
			cast->curr[0] = floor(info->player.x) - 0.0001;
		else
			cast->curr[0] = ceil(info->player.x);
		cast->delta[0] = fabs(cast->curr[0] - info->player.x) / \
						fabs(cast->ray[0]);
	}
	cast->curr[1] = info->player.y;
	if (fabs(cast->ray[1]) > 0.0001)
	{
		if (cast->ray[1] < -0.0001)
			cast->curr[1] = floor(info->player.y) - 0.0001;
		else
			cast->curr[1] = ceil(info->player.y);
		cast->delta[1] = fabs(cast->curr[1] - info->player.y) / \
						fabs(cast->ray[1]);
	}
	cast->prev_x = info->player.x;
	cast->prev_y = info->player.y;
	cast->is_wall = 0;
}

void	ft_player_color(int rgb[3])
{
	rgb[0] = 255;
	rgb[1] = 0;
	rgb[2] = 0;
}

void	ft_wall_color(int rgb[3])
{
	rgb[0] = 21;
	rgb[1] = 176;
	rgb[2] = 151;
}

void	ft_space_color(int rgb[3])
{
	rgb[0] = 72;
	rgb[1] = 86;
	rgb[2] = 150;
}

void	ft_door_color(int rgb[3])
{
	rgb[0] = 81;
	rgb[1] = 60;
	rgb[2] = 44;
}

//comparer x en fonction de la position dans la ligne et y en fonction de la ligne de la map. donc fonction pour dire si 1 -> mur, 2->porte etc
void	ft_init_color_map(t_info *info, int x, int y, int rgb[3])
{
	rgb[0] = 153;
	rgb[1] = 225;
	rgb[2] = 217;
	if (x == info->w - 110 && y == 90)
		ft_player_color(rgb);
}

int	ft_test_mapping(t_info *info, int x, int y)
{
	int	i;
	int	j;
	int	rgb[3];

	i = -1;
	ft_init_color_map(info, x, y, rgb);
	while (++i < 20)
	{
		j = -1;
		while (++j < 20)
		{
			if ((y == 10 && i == 0) || (x == info->w - 190 && j == 0) || (x == info->w - 30 && j == 19))
				my_mlx_pixel_put(&info->img, x + j, y + i, create_trgb(100, 0, 0, 0));
			else if (y == 170 && i == 19)
				my_mlx_pixel_put(&info->img, x + j, y + i, create_trgb(100, 0, 0, 0));
			else
				my_mlx_pixel_put(&info->img, x + j, y + i, create_trgb(100, rgb[0], rgb[1], rgb[2]));
		}
	}
	return (0);
}

int	ft_launch_map(t_info *info)
{
	int	x;
	int	y;

	y = 10; 
	while (y < 190)
	{
		x = info->w - 190;
		while (x < info->w - 10)
		{
			ft_test_mapping(info, x, y);
			x += 20;
		}
		y += 20;
	}
	return (0);
}

void	brice_casting(t_info *info)
{
	int			i;
	t_casting	cast;

	cast.proj_dist = 1;
	if (fabs(info->player.angle + M_PI / 2) < 0.0001)
		info->player.angle = 3 * M_PI * 2;
	else if (fabs(info->player.angle) < 0.0001)
		info->player.angle = 2 * M_PI;
	get_proj_screen(info, &cast);
	i = -1;
	cast.side = 0;
	while (++i < info->w)
	{
		casting2(info, &cast, i);
		while (cast.is_wall == 0)
		{
			if (fabs(cast.ray[0]) < 0.0001 || fabs(cast.ray[1]) < 0.0001)
				cast_droit(info, &cast);
			else
				cast_angle(info, &cast);
		}
		get_the_wall(info, &cast, i);
	}
	ft_launch_map(info);
	mlx_put_image_to_window(info->mlx, info->window, info->img.img, 0, 0);
}
