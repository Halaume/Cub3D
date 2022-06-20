/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brice_casting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:37:14 by ghanquer          #+#    #+#             */
/*   Updated: 2022/06/20 12:49:05 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	brice_casting(t_info *info)
{
	int	i;

	//Future struct cast a remplacer
//	double	perp_screen_x;
//	double	perp_screen_y;
	double	vect_x;
	double	vect_y;
//	double	pos_point_fov_left_x;
//	double	pos_point_fov_left_y;
//	double	pos_point_fov_right_x;
//	double	pos_point_fov_right_y;
	double	step;
	double	ray_x;
	double	ray_y;
	int		wall_height;
	int		fov_width;
	int		is_wall;

	i = -1;
	fov_width = 2;		//const -> fov90 + dist 1
	//ecran de vue a dist = 1 / angle tot = 90deg
//	perp_screen_x = info->my_pos_x + cos(90);
//	perp_screen_y = info->my_pos_y - sin(90);
	vect_x = cos(info->player.angle + (M_PI / 2));			//with const fov 90 -> -1
	vect_y = -sin(info->player.angle + (M_PI / 2));			//with const fov 90 -> 0
//	pos_point_fov_left_x = perp_screen_x + vect_x;
//	pos_point_fov_left_y = perp_screen_y + vect_y;
//	pos_point_fov_right_x = perp_screen_x - vect_x;
//	pos_point_fov_right_y = perp_screen_y - vect_y;
	step = fov_width/info->w;				//In my case 2/1920
	while (++i < info->w)
	{
		is_wall = 0;
		ray_x = info->player.x + (step * i);
		ray_y = info->player.y + (step * i);
		while (is_wall == 0)
		{
			if (info->map[(int)ray_x][(int)ray_y] == '1')
				is_wall = 1;
			else
			{
				ray_x += vect_x;
				ray_y += vect_y;
			}
		}
		wall_height = (info->h / 2) - ((info->w / 2)/(int)ray_y - info->player.y) / 2;
		put_col(info, wall_height, i);
	}
}
