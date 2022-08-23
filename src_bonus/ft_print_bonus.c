/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:50:14 by nflan             #+#    #+#             */
/*   Updated: 2022/08/03 15:30:25 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_print_mapping(t_map *map)
{
	if (map)
	{
		while (map)
		{
			printf("%s\n", map->line);
			map = map->next;
		}
	}
}

void	ft_print_text(t_info *info)
{
	if (info)
	{
		printf("Path text_n = '%s'\n", info->texture_n.path);
		printf("Path text_s = '%s'\n", info->texture_s.path);
		printf("Path text_w = '%s'\n", info->texture_w.path);
		printf("Path text_e = '%s'\n", info->texture_e.path);
		printf("Floor color = '%d'\n", info->color_floor);
		printf("Celling color = '%d'\n", info->color_sky);
		if (info->map)
			print_tab(info->map);
	}
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			printf("%s\n", tab[i]);
			i++;
		}
	}
}
