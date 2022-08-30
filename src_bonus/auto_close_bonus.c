/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_close_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:52:28 by ghanquer          #+#    #+#             */
/*   Updated: 2022/08/30 13:24:34 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

unsigned long long	get_now(t_info *info)
{
	unsigned long long	now;
	struct timeval		get_time;

	gettimeofday(&get_time, NULL);
	now = ((get_time.tv_sec - 1 - info->start.tv_sec) * 1000000) + \
			1000000 + (get_time.tv_usec - info->start.tv_usec);
	now = now / 1000;
	return (now);
}

void	door_closed(t_info *info)
{
	t_door			*tmp;
	unsigned int	now;

	now = get_now(info);
	tmp = info->door;
	while (tmp)
	{
		if (tmp->is_op == 1)
		{
			if (now - tmp->last_open > 5000)
				close_door(info, tmp);
		}
		tmp = tmp->next;
	}
}
