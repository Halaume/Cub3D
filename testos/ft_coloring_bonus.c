/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_coloring_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 11:21:00 by nflan             #+#    #+#             */
/*   Updated: 2022/08/18 11:21:01 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

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

void	ft_floor_color(int rgb[3])
{
	rgb[0] = 153;
	rgb[1] = 225;
	rgb[2] = 217;
}
