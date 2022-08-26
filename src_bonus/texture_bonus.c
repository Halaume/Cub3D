/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 11:10:49 by ghanquer          #+#    #+#             */
/*   Updated: 2022/08/26 15:58:32 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

/*void	get_address(t_info *info)
{
	info->texture_n.img.addr = mlx_get_data_addr(info->texture_n.img.img,
			&info->texture_n.img.bits_per_pixel,
			&info->texture_n.img.line_length, &info->texture_n.img.endian);
	info->texture_s.img.addr = mlx_get_data_addr(info->texture_s.img.img,
			&info->texture_s.img.bits_per_pixel,
			&info->texture_s.img.line_length, &info->texture_s.img.endian);
	info->texture_e.img.addr = mlx_get_data_addr(info->texture_e.img.img,
			&info->texture_e.img.bits_per_pixel,
			&info->texture_e.img.line_length, &info->texture_e.img.endian);
	info->texture_w.img.addr = mlx_get_data_addr(info->texture_w.img.img,
			&info->texture_w.img.bits_per_pixel,
			&info->texture_w.img.line_length, &info->texture_w.img.endian);
}

int	ft_open_exit_bonus(t_info *info)
{
	int			i;
	t_texture	*tmp;

	i = -1;
	tmp = info->fold_ex.sprite;
	while (++i < info->fold_ex.nb - 2)
	{
		printf("path = %s\n", tmp->path);
		printf("nb = %d\n", info->fold_ex.nb);
		if (tmp->path)
		{
			tmp->img.img = mlx_xpm_file_to_image(info->mlx, tmp->path,
					&tmp->width, &tmp->height);
			if (!tmp->img.img)
				return (ft_putstr_error("Error\nImpossible d'ouvrir la texture \
de sortie\n"));
			tmp->img.addr = mlx_get_data_addr(tmp->img.img,
						&tmp->img.bits_per_pixel, &tmp->img.line_length,
						&tmp->img.endian);
			if (!tmp->img.addr)
				return (ft_putstr_error("Error\nImpossible d'ouvrir la texture \
de sortie\n"));
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_open_bonus(t_info *info)
{
	if (info->texture_d.path)
	{
	}
	return (ft_open_exit_bonus(info));
}*/

int	ft_open_img(t_info *info, t_texture *text)
{
	if (text->path)
	{
		text->img.img = mlx_xpm_file_to_image(info->mlx, text->path,
				&text->width, &text->height);
		if (!text->img.img)
		{
			ft_putstr_error("Error\nImpossible d'ouvrir la texture: ");
			ft_putstr_error(text->path);
			return (ft_putstr_error("\n"));
		}
		text->img.addr = mlx_get_data_addr(text->img.img,
				&text->img.bits_per_pixel, &text->img.line_length,
				&text->img.endian);
		if (!text->img.addr)
		{
			ft_putstr_error("Error\nImpossible d'ouvrir la texture: ");
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
/*
	info->texture_n.img.img = mlx_xpm_file_to_image(info->mlx,
			info->texture_n.path, &info->texture_n.width,
			&info->texture_n.height);
	info->texture_s.img.img = mlx_xpm_file_to_image(info->mlx,
			info->texture_s.path, &info->texture_s.width,
			&info->texture_s.height);
	info->texture_e.img.img = mlx_xpm_file_to_image(info->mlx,
			info->texture_e.path, &info->texture_e.width,
			&info->texture_e.height);
	info->texture_w.img.img = mlx_xpm_file_to_image(info->mlx,
			info->texture_w.path, &info->texture_w.width,
			&info->texture_w.height);
	if (!info->texture_n.img.img || !info->texture_s.img.img
		|| !info->texture_e.img.img || !info->texture_w.img.img)
		return (ft_putstr_error("Error\nImpossible d'ouvrir une texture\n"));
	get_address(info);
	if (!info->texture_n.img.addr || !info->texture_s.img.addr
		|| !info->texture_e.img.addr || !info->texture_w.img.addr)
		return (ft_putstr_error("Error\nImpossible d'ouvrir une texture\n"));
	return (ft_open_bonus(info));
}*/
