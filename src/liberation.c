/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liberation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 14:44:56 by ghanquer          #+#    #+#             */
/*   Updated: 2022/08/03 13:20:48 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_char_char(char **str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return ;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}

void	free_texture(t_info *info, t_texture texture)
{
	if (texture.img.img)
		mlx_destroy_image(info->mlx, texture.img.img);
	if (texture.path)
		free(texture.path);
}

void	ft_free_map(t_map *map)
{
	t_map	*tmp;

	if (!map)
		return ;
	while (map)
	{
		tmp = map;
		map = map->next;
		free(tmp->line);
		tmp->line = NULL;
		free(tmp);
	}
}

void	ft_free(t_info *info)
{
	if (info->fd)
		close(info->fd);
	if (info->texture_n.path)
		free(info->texture_n.path);
	info->texture_n.path = NULL;
	if (info->texture_s.path)
		free(info->texture_s.path);
	info->texture_s.path = NULL;
	if (info->texture_w.path)
		free(info->texture_w.path);
	info->texture_w.path = NULL;
	if (info->texture_e.path)
		free(info->texture_e.path);
	info->texture_e.path = NULL;
	if (info->mapping)
		ft_free_map(info->mapping);
}

void	free_func(t_info *info)
{
	free_char_char(info->map);
	free_texture(info, info->texture_n);
	free_texture(info, info->texture_s);
	free_texture(info, info->texture_e);
	free_texture(info, info->texture_w);
	if (info)
		ft_free(info);
}
