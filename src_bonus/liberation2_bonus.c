/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liberation2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 11:23:14 by nflan             #+#    #+#             */
/*   Updated: 2022/08/24 11:47:24 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

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
