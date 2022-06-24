/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affiche.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:08:55 by ghanquer          #+#    #+#             */
/*   Updated: 2022/06/24 15:18:50 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	put_col(t_info *info, int start_px, int end_px, int y)
{
	int	color_wall;
	int	i;

	color_wall = 0x00FF0000;
	i = -1;
	while (++i < start_px)
		my_mlx_pixel_put(&info->img, y, i, info->color_sky);
	while (++i < end_px)
		my_mlx_pixel_put(&info->img, y, i, color_wall);
	while (++i < info->h)
		my_mlx_pixel_put(&info->img, y, i, info->color_floor);
}
