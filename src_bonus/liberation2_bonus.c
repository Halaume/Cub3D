/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liberation2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 11:23:14 by nflan             #+#    #+#             */
/*   Updated: 2022/09/01 11:20:28 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

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

void	free_texture(t_info *info, t_texture *texture)
{
	if (texture->img.img)
		mlx_destroy_image(info->mlx, texture->img.img);
	texture->img.img = NULL;
	if (texture->path)
		free(texture->path);
	texture->path = NULL;
}

void	free_sprite(t_texture *tmp, t_info *info)
{
	free(tmp->path);
	tmp->path = NULL;
	if (tmp->img.img)
		free_texture(info, tmp);
}

void	ft_free_doors(t_door *door)
{
	t_door	*tmp;

	while (door)
	{
		tmp = door;
		door = door->next;
		free(tmp);
		tmp = NULL;
	}
}
