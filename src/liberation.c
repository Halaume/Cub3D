/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liberation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 14:44:56 by ghanquer          #+#    #+#             */
/*   Updated: 2022/06/17 14:26:01 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_char_char(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_func(t_info *info)
{
	free_char_char(info->map);
	//	TODO
	//	free_all
}
