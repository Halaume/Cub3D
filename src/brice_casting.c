/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brice_casting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:37:14 by ghanquer          #+#    #+#             */
/*   Updated: 2022/06/27 15:42:41 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	brice_casting(t_info *info)
{
	int	i;
	int	proj_dist;
	//ecran de vue a dist = 1 / angle tot = 90deg

	//Future struct cast a remplacer
	double	ray[2];				//x,y
	double	proj_screen[4];		//[0][1] == x,y gauche / [2][3] == x,y droite
	double		wall_height;
	int		is_wall;
	double	dir_v_x;
	double	dir_v_y;
	double	curr[2];		//encore aled
	double	prev_x;
	double	prev_y;
	int		start_px;
	int		end_px;
//	char	*dist;
//	char	*origin;
	double	delta[2];		//x,y
	double	distance0;
	double	distance1;
	double	wall_ratio;
	double	tmp[2];		//ALED
	double	percent;
	int		autre;
	int		side;

	proj_dist = 1;

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



	i = -1;
	side = 0;
	while (++i < info->w)
	{
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

		prev_x = info->player.x;
		prev_y = info->player.y;
		is_wall = 0;
		while (is_wall == 0)
		{
			if (fabs(ray[0]) < 0.0001 || fabs(ray[1]) < 0.0001)
			{
				if (fabs(ray[0]) < 0.0001)
				{
					if (info->map[(int)curr[1]][(int)curr[0]] == '1')
						is_wall = 1;
					else
					{
						curr[1] += 1;
						if (ray[1] < 0)
							curr[1] -= 2;
					}
				}
				else
				{
					if (info->map[(int)curr[1]][(int)curr[0]] == '1')
						is_wall = 2;
					else
					{
						curr[0] += 1;
						if (ray[0] < 0)
							curr[0] -= 2;
					}
				}
			}
			else
			{
				if (fabs(delta[0] - delta[1]) < 0.0001 || delta[0] < delta[1])
				{
					curr[1] = delta[0] * ray[1] + prev_y;
					side = 0;
					if (info->map[(int)curr[1]][(int)curr[0]] == '1')
						is_wall = 2;
				}
				else
				{
					curr[0] = delta[1] * ray[0] + prev_x;
					side = 1;
					if (info->map[(int)curr[1]][(int)curr[0]] == '1')
						is_wall = 1;
				}
				if (is_wall == 0)
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
			if (is_wall != 0)
				printf("Touching wall at : %f | %f / (int)%d | (int)%d\n", curr[0], curr[1], (int)curr[0], (int)curr[1]);
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


		//Draw_Strip
		if (is_wall == 1)
		{
			percent = (curr[0] - floor(curr[0])) / 1;
			//texture = no;
			if (ray[1] > 0)
			{
				//texture = so;
				percent = 1 - percent;
			}
		}
		else
		{
			//texture = ea;
			percent = (curr[1] - floor(curr[1])) / 1;
			if (ray[0] < 0)
			{
				//texture = we;
				percent = 1 - percent;
			}
		}
		if (percent >= 1)
			percent = 0.9999;
		percent = floor(percent * (double)128); // texture_width
		if (wall_height < 0)
			start_px = 1;
		else
			start_px = (int)floor((((double)info->h - 1 ) / 2) - ((double)wall_height / 2));
		if (wall_height >= info->h)
			end_px = info->h;
		else
			end_px = start_px + wall_height - 1;
		put_col(info, start_px, end_px, i, percent, wall_height);
	}
	mlx_put_image_to_window(info->mlx, info->window, info->img.img, 0, 0);
}


//		dist = info->img.addr + i * (info->img.bits_per_pixel / 8);
//		origin = /*texture.texture.addr + */(int)percent/* * (texture.texture.bits_per_pixel / 8)*/;
//		step = ((double)1 / (double)wall_height)/* * (double)(texture.height)*/;
//		int	it;
//		double	current;
//		int		percent_y;
//		it = 0;
//		while (it < info->h && it < start_px)
//		{
//			*(unsigned int *)dist = info->color_sky;
//			dist += info->img.line_length;
//			it++;
//		}
//		current = (double)(it - start_px) * step;
//		while (it < info->h &&it <= end_px)
//		{
//			percent_y = (int)current;
//			if (percent_y == texture.height)
//				percent_y = texture.height - 1;
//			*(unsigned int *)dist = info->img->addr + /**(unsigned int *)(origin + */(int)percent_y * info->img->line_lenght/* * texture.texture.line_lenght)*/;
//			dist += info->img.line_length;
//			current += step;
//			it++;
//		}
//		while (it < info->h)
//		{
//			*(unsigned int *)dist = info->color_floor;
//			dist += info->img.line_length;
//			it++;
//		}
