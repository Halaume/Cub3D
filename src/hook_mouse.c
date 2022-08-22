/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:55:48 by ghanquer          #+#    #+#             */
/*   Updated: 2022/08/22 14:18:55 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	hook_mouse(int keycode, int x, int y, t_info *info)
{
	(void)x;
	(void)y;
	printf("keycode = %d\n", keycode);
	if (keycode == 1)
		info->hook.mouse_hold = 1;
	looping_hook(info);
	return (0);
}

int	hook_mouse_release(int keycode, int x, int y, t_info *info)
{
	(void)x;
	(void)y;
	printf("keycode = %d\n", keycode);
	if (keycode == 1)
		info->hook.mouse_hold = 0;
	looping_hook(info);
	return (0);
}

int	hook_mouse_mouv(int x, int y, t_info *info)
{
	(void)y;
	printf("keycode = %d\n", x);
	info->hook.mouse_prev_pos = info->hook.mouse_pos;
	info->hook.mouse_pos = x;
	looping_hook(info);
	return (0);
}
