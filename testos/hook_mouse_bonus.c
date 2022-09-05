/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_mouse_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:55:48 by ghanquer          #+#    #+#             */
/*   Updated: 2022/09/01 13:07:21 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

int	hook_mouse(int keycode, int x, int y, t_info *info)
{
	(void)y;
	if (keycode == 1)
	{
		info->hook.mouse_pos = x;
		info->hook.mouse_prev_pos = x;
		info->hook.mouse_hold = 1;
	}
	return (0);
}

int	hook_mouse_release(int keycode, int x, int y, t_info *info)
{
	(void)x;
	(void)y;
	if (keycode == 1)
		info->hook.mouse_hold = 0;
	return (0);
}

int	hook_mouse_mouv(int x, int y, t_info *info)
{
	(void)y;
	if (info->hook.mouse_hold)
		info->hook.mouse_pos = x;
	return (0);
}
