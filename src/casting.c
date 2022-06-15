/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 14:42:39 by ghanquer          #+#    #+#             */
/*   Updated: 2022/06/15 17:55:40 by ghanquer         ###   ########.fr       */
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

	i = 0;
	go_x = 1;
	go_y = 1;
	while (i < 10)
	{
		is_wall = 0;
		ray_pos_x = 2 * i / 9; //map len - 1
		ray_dir_x = info->dir_x + info->view_x * ray_pos_x;
		ray_dir_y = info->dir_y + info->view_y * ray_pos_x;
		map_x = info->my_pos_x;
		map_y = info->my_pos_y;
		delta_dir_x = sqrt(1 + (ray_dir_y * ray_dir_y) / (ray_dir_x * ray_dir_x));
		delta_dir_y = sqrt(1 + (ray_dir_x * ray_dir_x) / (ray_dir_y * ray_dir_y));
		i++;
	}
}
