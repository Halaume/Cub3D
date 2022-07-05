/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liberation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 14:44:56 by ghanquer          #+#    #+#             */
/*   Updated: 2022/07/05 15:43:51 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_char_char(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_texture(t_info *info, t_texture texture)
{
	if (texture.img.img)
		mlx_destroy_image(info->mlx, texture.img.img);
	if (texture.path)
		free(texture.path);
}

void	free_func(t_info *info)
{
	free_char_char(info->map);
	free_texture(info, info->texture_n);
	free_texture(info, info->texture_s);
	free_texture(info, info->texture_e);
	free_texture(info, info->texture_w);

	//	TODO
	//	free_all
}
