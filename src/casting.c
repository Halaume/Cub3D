/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 14:42:39 by ghanquer          #+#    #+#             */
/*   Updated: 2022/06/16 12:42:18 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	casting(t_info *info)
{
	int		i;
	double	ray_pos_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	int		is_wall;
	int		go_x;
	int		go_y;
	double	next_x;
	double	next_y;
	double	delta_dir_x;
	double	delta_dir_y;
	double	wall_start;
	double	wall_end;
	double	perp_dist;
	int		case_x;
	int		case_y;
	int		side;
	int		line_h;

	i = 0;
	go_x = 1;
	go_y = 1;
	while (i < 10) //map len
	{
		case_x = (int)info->my_pos_x;
		case_y = (int)info->my_pos_y;
		is_wall = 0;
		ray_pos_x = 2 * i / 9; //map len - 1
		ray_dir_x = info->dir_x + info->view_x * ray_pos_x;
		ray_dir_y = info->dir_y + info->view_y * ray_pos_x;
		map_x = info->my_pos_x;
		map_y = info->my_pos_y;
		delta_dir_x = sqrt(1 + (ray_dir_y * ray_dir_y) / (ray_dir_x * ray_dir_x));
		delta_dir_y = sqrt(1 + (ray_dir_x * ray_dir_x) / (ray_dir_y * ray_dir_y));
		if (ray_dir_x < 0)
		{
			go_x = -1;
			next_x = (info->my_pos_x - case_x) * delta_dir_x;
		}
		else
		{
			go_x = 1;
			next_x = (case_x + 1.0 - info->my_pos_x) * delta_dir_x;
		}
		if (ray_dir_y < 0)
		{
			go_y = -1;
			next_y = (info->my_pos_y - case_y) * delta_dir_y;
		}
		else
		{
			go_y = 1;
			next_y = (case_y + 1.0 - info->my_pos_y) * delta_dir_y;
		}
		while (is_wall == 0)
		{
			if (next_x < next_y)
			{
				go_x += delta_dir_x;
				case_x += go_x;
				side = 0; //fix side hit N/S
			}
			else
			{
				go_y += delta_dir_y;
				case_y += go_y;
				side = 1; //fix side hit E/W;
			}
			if (info->map[case_x][case_y] > 0) 
				is_wall = 1;


			if(side == 0)
				perp_dist = (go_x - delta_dir_x);
			else
				perp_dist = (go_y - delta_dir_y);
			line_h = (int)(info->h / perp_dist);
			wall_start = -line_h / 2 + info->h / 2;
			if(wall_start < 0)
				wall_start = 0;
			wall_end = line_h / 2 + info->h / 2;
			if(wall_end >= info->h)
				wall_end = info->h - 1;
			//Put_pixels of all col
		}
		i++;
	}
}
