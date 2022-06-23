/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brice_casting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:37:14 by ghanquer          #+#    #+#             */
/*   Updated: 2022/06/23 17:33:35 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	brice_casting(t_info *info)
{
	int	i;
	int	proj_dist;
//ecran de vue a dist = 1 / angle tot = 90deg

	//Future struct cast a remplacer
//	double	perp_screen_x;
//	double	perp_screen_y;
//	double	vect_x;
//	double	vect_y;
//	double	pos_point_fov_left_x;
//	double	pos_point_fov_left_y;
//	double	pos_point_fov_right_x;
//	double	pos_point_fov_right_y;
//	double	step;
	double	ray[2];				//x,y
	double	proj_screen[4];		//[0][1] == x,y gauche / [2][3] == x,y droite
	int		wall_height;
//	int		fov_width;
	int		is_wall;
	double	dir_v_x;
	double	dir_v_y;
	int		curr[2];		//encore aled
	int		prev_x;
	int		prev_y;
	double	delta[2];		//x,y
	double	distance0;
	double	distance1;
	double	wall_ratio;
	double	tmp[2];		//ALED
	int		autre;
	int		side;

	proj_dist = 1;
//	fov_width = 2;		//const -> fov90 + dist 1
//	step = (double)fov_width / (double)info->w;				//In my case 2/1920
//	perp_screen_x = info->my_pos_x + cos(info->player.angle);
//	perp_screen_y = info->my_pos_y - sin(info->player.angle);

	if (fabs(info->player.angle + M_PI / 2) < 0.0001)
		info->player.angle = 3 * M_PI * 2;
	else if (fabs(info->player.angle) < 0.0001)
		info->player.angle = 2 * M_PI;

	proj_screen[0] = info->player.angle + (M_PI / 4);
	proj_screen[1] = (-sin(proj_screen[0])) * ((double)proj_dist / cos(M_PI / 4)) + info->player.y;
	proj_screen[0] = (cos(proj_screen[0])) * ((double)proj_dist / cos(M_PI / 4)) + info->player.x;
	proj_screen[2] = info->player.angle - (M_PI / 4);
	proj_screen[3] = (-sin(proj_screen[2])) * ((double)proj_dist / cos(M_PI / 4)) + info->player.y;
	proj_screen[2] = (cos(proj_screen[2])) * ((double)proj_dist / cos(M_PI / 4)) + info->player.x;


	dir_v_x = (proj_screen[2] - proj_screen[0]) / (double)(info->w - 1);
	dir_v_y = (proj_screen[3] - proj_screen[1]) / (double)(info->w - 1);
//	vect_x = cos(info->player.angle + (M_PI / 2));			//with const fov 90 -> -1
//	vect_y = -sin(info->player.angle + (M_PI / 2));			//with const fov 90 -> 0
//	pos_point_fov_left_x = perp_screen_x + vect_x;
//	pos_point_fov_left_y = perp_screen_y + vect_y;
//	pos_point_fov_right_x = perp_screen_x - vect_x;
//	pos_point_fov_right_y = perp_screen_y - vect_y;
	curr[0] = info->player.x;
	curr[1] = info->player.y;
	i = -1;
	side = 0;
	while (++i < info->w)
	{
		is_wall = 0;
		ray[0] = (proj_screen[0] + dir_v_x * i) - info->player.x;
		ray[1] = (proj_screen[1] + dir_v_y * i) - info->player.y;
		curr[0] = info->player.x;
		if (fabs(ray[0]) > 0.0001)
		{
			if (ray[0] < -0.0001)
				curr[0] = floor(info->player.x) - 0.0001;
			else
				curr[0] = ceil(info->player.x);
			delta[0] = fabs(curr[0] - info->player.x) / fabs(ray[0]);
		}
		curr[1] = info->player.y;
		if (fabs(ray[1]) > 0.0001)
		{
			if (ray[1] < -0.0001)
				curr[1] = floor(info->player.y) - 0.0001;
			else
				curr[1] = ceil(info->player.y);
			delta[1] = fabs(curr[1] - info->player.y) / fabs(ray[1]);
		}

//		ray_x = info->player.x + (step * i);
//		ray_y = info->player.y + (step * i);
		prev_x = info->player.x;
		prev_y = info->player.y;
		while (is_wall == 0)
		{
			printf("angle = %f\n", info->player.angle);
			if (fabs(ray[0]) < 0.0001 || fabs(ray[1]) < 0.0001)
			{
				if (info->map[(int)curr[1]][(int)curr[0]] == '1')
					is_wall = 1;
				else
				{
					curr[0] += 1;
					if (ray[0] < 0)
						curr[0] -= 2;
				}
				if (ray[1] == 0)
					ray[1] = 0.00001;
				if (ray[0] == 0)
					ray[0] = 0.00001;
			}
			else
			{
				if (fabs(delta[0] - delta[1]) < 0.0001 || delta[0] < delta[1])
				{
					curr[1] = delta[0] * ray[1] + prev_y;
					side = 0;
				}
				else
				{
					curr[0] = delta[1] * ray[0] + prev_x;
					side = 1;
				}
				if (info->map[(int)curr[1]][(int)curr[0]] == '1')
					is_wall = 1;
				else
				{
					prev_x = curr[0];
					prev_y = curr[1];
					//	TRYING BRICE'S GET NEXT EDGE
					autre = side ^ 1;//side = 0 ou 1 donc pour check les 2 XOR sur autre
					if (ray[side] < 0)
						tmp[side] = curr[side] - 1;
					else
						tmp[side] = curr[side] + 1;
					delta[side] = fabs(tmp[side] - curr[side]) / fabs(ray[side]);
					if (ray[autre] < 0)
						tmp[autre] = floor(curr[autre] - 0.0001);
					else
						tmp[autre] = ceil(curr[autre]);
					delta[autre] = fabs(tmp[autre] - curr[autre]) / fabs(ray[autre]);
					if (fabs(delta[autre]) < 0.0001)
						tmp[autre] += 0.0001;
					delta[autre] = fabs(tmp[autre] - curr[autre]) / fabs(ray[autre]);
					curr[0] = tmp[0];
					curr[1] = tmp[1];
					//
				}
			}
		}


		if (fabs(curr[0] - info->player.x) < 0.0001)
			distance0 = fabs(curr[1] - info->player.y);
		else if (fabs(curr[1] - info->player.y) < 0.0001)
			distance0 = fabs(curr[0] - info->player.x);
		else
			distance0 = hypot(fabs(curr[0] - info->player.x), fabs(curr[1] - info->player.y));
		if (fabs(ray[0]) < 0.0001)
			distance1 = fabs(ray[1]);
		else if (fabs(ray[1]) < 0.0001)
			distance1 = fabs(ray[0]);
		else
			distance1 = hypot(fabs(ray[0]), fabs(ray[1]));
		wall_ratio = distance1 / distance0;
		wall_height = (int)round(wall_ratio * ((double)info->w / 2));


//		printf("ray_y = %f && info->player.y = %f\n", ray_y, info->player.y / 1);
//		wall_height = (int)round((fabs(ray_y) / fabs(ray_x)) * ((double)info->w / 2));
//		printf("Wall_height = %d\n", wall_height);
//		wall_height = (int)((info->h / 2) - ((info->w / 2)/ray_y) - info->player.y / 2);
//		printf("%d\n", wall_height);
		put_col(info, wall_height, i);
	}
	mlx_put_image_to_window(info->mlx, info->window, info->img.img, 0, 0);
}
