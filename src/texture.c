/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 11:10:49 by ghanquer          #+#    #+#             */
/*   Updated: 2022/06/30 13:54:36 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char	*get_texture_path(void)
{
	return ("texture/wall.xpm");
}

t_data	get_texture(t_info *info)
{
	t_data	my_texture;

	info->texture_path = get_texture_path();
	mlx_xpm_file_to_image(info->mlx, info->texture_path, &my_texture.width, &my_texture.height);
	my_texture.img = mlx_new_image(info->mlx, my_texture.width, my_texture.height);
	my_texture.addr = mlx_get_data_addr(my_texture.img, &my_texture.bits_per_pixel, &my_texture.line_length, &my_texture.endian);
	return (my_texture);
}
