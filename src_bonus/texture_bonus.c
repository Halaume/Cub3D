/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 11:10:49 by ghanquer          #+#    #+#             */
/*   Updated: 2022/08/26 12:56:58 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

void	get_address(t_info *info)
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

/*int	ft_open_exit_bonus(t_info *info)
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
}*/

int	ft_open_bonus(t_info *info)
{
	if (info->texture_d.path)
	{
		info->texture_d.img.img = mlx_xpm_file_to_image(info->mlx,
				info->texture_d.path, &info->texture_d.width,
				&info->texture_d.height);
		if (!info->texture_d.img.img)
			return (ft_putstr_error("Error\nImpossible d'ouvrir la texture de \
porte\n"));
		info->texture_d.img.addr = mlx_get_data_addr(info->texture_d.img.img,
				&info->texture_d.img.bits_per_pixel,
				&info->texture_d.img.line_length, &info->texture_d.img.endian);
		if (!info->texture_d.img.addr)
			return (ft_putstr_error("Error\nImpossible d'ouvrir la texture de \
porte\n"));
	}
	return (0);
//	return (ft_open_exit_bonus(info));
}

int	get_texture(t_info *info)
{
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
}
