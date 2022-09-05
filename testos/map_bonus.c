/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:30:28 by ghanquer          #+#    #+#             */
/*   Updated: 2022/09/01 12:21:32 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

void	ft_mapadd_back(t_map **map, t_map *new)
{
	t_map	*tmp;

	tmp = *map;
	if (map && new)
	{
		if (*map == NULL)
			*map = new;
		else
		{
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
	}
}

int	ft_mapnew(t_map **map, char *buf)
{
	t_map	*new;

	new = ft_calloc(sizeof(t_map), 1);
	if (!new)
		return (ft_putstr_error("Error\nMalloc error\n"));
	new->line = ft_strtrim(buf, "\n");
	if (!new->line)
		return (free(new), ft_putstr_error("Error\nMalloc error\n"));
	ft_mapadd_back(map, new);
	return (0);
}

size_t	ft_maplen(t_map *chain)
{
	size_t	i;

	i = 0;
	if (!chain)
		return (i);
	if (chain)
	{
		while (chain)
		{
			chain = chain->next;
			i++;
		}
	}
	return (i);
}

size_t	ft_longest(t_map *map)
{
	size_t	i;

	i = 0;
	if (!map)
		return (-1);
	while (map)
	{
		if (i < ft_strlen(map->line))
			i = ft_strlen(map->line);
		map = map->next;
	}
	return (i);
}

int	ft_getmap(t_info *info)
{
	t_map	*tmp;
	size_t	len;
	int		i;

	i = 0;
	tmp = info->mapping;
	if (!info->mapping)
		return (ft_putstr_error("Error\nNo map detected\n"));
	len = ft_longest(info->mapping);
	info->map = ft_calloc(sizeof(char *), ft_maplen(info->mapping) + 1);
	if (!info->map)
		return (ft_putstr_error("Error\nMalloc error\n"));
	while (tmp)
	{
		info->map[i] = ft_substr_map(tmp->line, 0, len);
		if (!info->map[i])
			return (ft_putstr_error("Error\nMalloc error\n"));
		i++;
		tmp = tmp->next;
	}
	return (0);
}
