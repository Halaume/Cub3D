/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:30:28 by ghanquer          #+#    #+#             */
/*   Updated: 2022/08/02 17:36:18 by nflan            ###   ########.fr       */
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
