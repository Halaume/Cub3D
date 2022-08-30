/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 11:10:49 by ghanquer          #+#    #+#             */
/*   Updated: 2022/08/30 13:20:09 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

int	ft_open_img(t_info *info, t_texture *text)
{
	if (text->path)
	{
		text->img.img = mlx_xpm_file_to_image(info->mlx, text->path,
				&text->width, &text->height);
		if (!text->img.img)
		{
			ft_putstr_error("Error\nError while opening the texture: ");
			ft_putstr_error(text->path);
			return (ft_putstr_error("\n"));
		}
		text->img.addr = mlx_get_data_addr(text->img.img,
				&text->img.bits_per_pixel, &text->img.line_length,
				&text->img.endian);
		if (!text->img.addr)
		{
			ft_putstr_error("Error\nError while opening the texture: ");
			ft_putstr_error(text->path);
			return (ft_putstr_error("\n"));
		}
	}
	return (0);
}

int	ft_init_img(t_info *info, t_texture *text)
{
	int	b;

	b = 0;
	if (!text)
		return (1);
	while (text->index != 0 || b == 0)
	{
		b = 1;
		if (ft_open_img(info, text))
			return (1);
		if (text->next)
			text = text->next;
	}
	return (0);
}

int	get_texture(t_info *info)
{
	if (ft_init_img(info, info->texture_n))
		return (1);
	if (ft_init_img(info, info->texture_s))
		return (1);
	if (ft_init_img(info, info->texture_e))
		return (1);
	if (ft_init_img(info, info->texture_w))
		return (1);
	if (info->texture_d)
		if (ft_init_img(info, info->texture_d))
			return (1);
	if (info->texture_ex)
		if (ft_init_img(info, info->texture_ex))
			return (1);
	return (0);
}
