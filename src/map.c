/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:30:28 by ghanquer          #+#    #+#             */
/*   Updated: 2022/08/03 15:30:43 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char	**get_map(int fd)
{
	char	**map;
	int		i;

	map = ft_calloc(sizeof(char *), 11);
	if (!map)
		return (NULL);
	i = 0;
	while (i < 10)
	{
		map[i] = get_next_line(fd);
		printf("%s", map[i]);
		i++;
	}
	printf("\n");
	close(fd);
	return (map);
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
		return (1);
	len = ft_longest(info->mapping);
	info->map = ft_calloc(sizeof(char *), ft_maplen(info->mapping) + 1);
	if (!info->map)
		return (ft_putstr_error("Error\nMalloc error\n"));
	while (tmp)
	{
		info->map[i] = ft_substr(tmp->line, 0, len);
		if (!info->map[i])
			return (ft_putstr_error("Error\nMalloc error\n"));
		i++;
		tmp = tmp->next;
	}
	return (0);
}
