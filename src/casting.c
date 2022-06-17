/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 14:42:39 by ghanquer          #+#    #+#             */
/*   Updated: 2022/06/17 16:46:11 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	casting(t_info *info)
{
	int			i;
	t_casting	cast;

	cast.go_x = 1;
	cast.go_y = 1;
	i = 0;
	while (i < 1920) //window width
	{
		cast.case_x = (int)info->my_pos_x;
		cast.case_y = (int)info->my_pos_y;
		cast.is_wall = 0;
		cast.ray_pos_x = 2 * i / 9; //map len - 1
		cast.ray_dir_x = info->dir_x + info->view_x * cast.ray_pos_x;
		cast.ray_dir_y = info->dir_y + info->view_y * cast.ray_pos_x;
		if (cast.ray_dir_x == 0)
			cast.ray_dir_x = 1;
		if (cast.ray_dir_y == 0)
			cast.ray_dir_y = 1;
		cast.map_x = info->my_pos_x;
		cast.map_y = info->my_pos_y;
		cast.delta_dir_x = sqrt(1 + (cast.ray_dir_y * cast.ray_dir_y) / (cast.ray_dir_x * cast.ray_dir_x));
		cast.delta_dir_y = sqrt(1 + (cast.ray_dir_x * cast.ray_dir_x) / (cast.ray_dir_y * cast.ray_dir_y));
		if (cast.ray_dir_x < 0)
		{
			cast.go_x = -1;
			cast.next_x = (info->my_pos_x - cast.case_x) * cast.delta_dir_x;
		}
		else
		{
			cast.go_x = 1;
			cast.next_x = (cast.case_x + 1.0 - info->my_pos_x) * cast.delta_dir_x;
		}
		if (cast.ray_dir_y < 0)
		{
			cast.go_y = -1;
			cast.next_y = (info->my_pos_y - cast.case_y) * cast.delta_dir_y;
		}
		else
		{
			cast.go_y = 1;
			cast.next_y = (cast.case_y + 1.0 - info->my_pos_y) * cast.delta_dir_y;
		}
		while (cast.is_wall == 0)
		{
			if (cast.next_x < cast.next_y)
			{
				cast.go_x += (int)cast.delta_dir_x;
				cast.case_x += cast.go_x;
				cast.side = 0; //fix side hit N/S
			}
			else
			{
				cast.go_y += (int)cast.delta_dir_y;
				cast.case_y += cast.go_y;
				cast.side = 1; //fix side hit E/W;
			}
			if (info->map[cast.case_x][cast.case_y] > '0') 
				cast.is_wall = 1;
			if (cast.side == 0)
				cast.perp_dist = (cast.go_x - cast.delta_dir_x);
			else
				cast.perp_dist = (cast.go_y - cast.delta_dir_y);
			cast.line_h = (int)(info->h / cast.perp_dist);
			cast.wall_start = -cast.line_h / 2 + info->h / 2;
			if ((int)cast.wall_start < 0)
				cast.wall_start = 0;
			cast.wall_end = cast.line_h / 2 + info->h / 2;
			if ((int)cast.wall_end >= info->h)
				cast.wall_end = info->h - 1;
		}
		put_col(info, cast, i); //Put_pixels of a col
		i++;
	}
	mlx_put_image_to_window(info->mlx, info->window, info->img.img, 0, 0);
}
