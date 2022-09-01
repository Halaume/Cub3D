/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite_tools_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:22:45 by nflan             #+#    #+#             */
/*   Updated: 2022/09/01 11:24:32 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

void	ft_spriteadd_back(t_texture **sprite, t_texture *new)
{
	t_texture	*tmp;

	tmp = *sprite;
	if (sprite && new)
	{
		if (*sprite == NULL)
			*sprite = new;
		else
		{
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
	}
}

int	ft_sprite_new(t_texture **text, char *path, int i)
{
	t_texture	*new;

	new = ft_calloc(sizeof(t_texture), 1);
	if (!new)
		return (ft_putstr_error("Error\nMalloc error"));
	new->path = ft_strdup(path);
	new->index = i;
	ft_spriteadd_back(text, new);
	return (0);
}
