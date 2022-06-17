/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:30:28 by ghanquer          #+#    #+#             */
/*   Updated: 2022/06/16 15:23:30 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char	**get_map(int fd)
{
	char	**map;
	int		i;

	map = malloc(sizeof(char *) * 11);
	if (!map)
		return (NULL);
	map[10] = NULL;
	i = 0;
	while (i < 10)
	{
		map[i] = get_next_line(fd);
		i++;
	}
	close(fd);
	return (map);
}
