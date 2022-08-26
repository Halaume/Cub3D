/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:12:32 by ghanquer          #+#    #+#             */
/*   Updated: 2022/08/26 15:44:16 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

void	pls_help_exit(t_info *info, t_casting *cast, int i)
{
	cast->texture = *info->fold_ex.sprite;
	if (cast->wall_height < 0)
		cast->start_px = 1;
	else
		cast->start_px = (int)floor((((double)info->h - 1) / 2) - \
				((double)cast->wall_height / 2));
	if (cast->wall_height >= info->h)
		cast->end_px = info->h;
	else
		cast->end_px = cast->start_px + cast->wall_height - 1;
	put_col(info, cast, i);
}

void	get_the_exit(t_info *info, t_casting *cast, int i)
{
	if (fabs(cast->curr[0] - info->player.x) < 0.0001)
		cast->distance0 = fabs(cast->curr[1] - info->player.y);
	else if (fabs(cast->curr[1] - info->player.y) < 0.0001)
		cast->distance0 = fabs(cast->curr[0] - info->player.x);
	else
		cast->distance0 = hypot(fabs(cast->curr[0] - info->player.x), \
				fabs(cast->curr[1] - info->player.y));
	if (fabs(cast->ray[0]) < 0.0001)
		cast->distance1 = fabs(cast->ray[1]);
	else if (fabs(cast->ray[1]) < 0.0001)
		cast->distance1 = fabs(cast->ray[0]);
	else
		cast->distance1 = hypot(fabs(cast->ray[0]), fabs(cast->ray[1]));
	cast->wall_ratio = cast->distance1 / cast->distance0;
	cast->wall_height = (int)round(cast->wall_ratio * ((double)info->w / 2));
	pls_help_exit(info, cast, i);
}
