/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liberation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 14:44:56 by ghanquer          #+#    #+#             */
/*   Updated: 2022/08/30 18:18:59 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

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

void	free_texture(t_info *info, t_texture *texture)
{
	if (texture->img.img)
		mlx_destroy_image(info->mlx, texture->img.img);
	texture->img.img = NULL;
	if (texture->path)
		free(texture->path);
	texture->path = NULL;
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
		tmp = NULL;
	}
}

void	free_sprite(t_texture *tmp, t_info *info)
{
	free(tmp->path);
	tmp->path = NULL;
	if (tmp->img.img)
		free_texture(info, tmp);
}

int	ft_count_ind(t_texture *text)
{
	int	i;

	i = 0;
	if (!text)
		return (-1);
	if (!text->next)
		return (0);
	while (text->next)
	{
		if (text->next && text->next->index == 0)
			break ;
		text = text->next;
	}
	return (text->index);
}

void	ft_free_texture(t_info *info, t_texture *text)
{
	t_texture	*tmp;
	int			i;

	i = ft_count_ind(text) + 1;
	if (text)
	{
		while (text && i--)
		{
			tmp = text;
			text = text->next;
			if (tmp && tmp->path)
				free_sprite(tmp, info);
			free(tmp);
			tmp = NULL;
		}
	}
	text = NULL;
}

void	ft_free(t_info *info)
{
	if (info->fd)
		close(info->fd);
	if (info->texture_n)
		ft_free_texture(info, info->texture_n);
	if (info->texture_s)
		ft_free_texture(info, info->texture_s);
	if (info->texture_e)
		ft_free_texture(info, info->texture_e);
	if (info->texture_w)
		ft_free_texture(info, info->texture_w);
	if (info->texture_d)
		ft_free_texture(info, info->texture_d);
	if (info->texture_ex)
		ft_free_texture(info, info->texture_ex);
	if (info->mapping)
		ft_free_map(info->mapping);
	if (info->map)
		ft_free_split(info->map);
	if (info->door)
		ft_free_doors(info->door);
}
