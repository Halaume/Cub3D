/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:40:59 by ghanquer          #+#    #+#             */
/*   Updated: 2022/06/28 12:00:32 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	hook(int keycode, t_info *info)
{
	printf("Keycode : %d\n", keycode);
	if (keycode == 65361)
		info->hook.cam_left = 1;
	if (keycode == 65363)
		info->hook.cam_right = 1;
	if (keycode == 65362)
		info->hook.forward2 = 1;
	if (keycode == 65364)
		info->hook.backward2 = 1;
	if (keycode == 97)
		info->hook.left = 1;
	if (keycode == 100)
		info->hook.right = 1;
	if (keycode == 119)
		info->hook.forward = 1;
	if (keycode == 115)
		info->hook.backward = 1;
	if (keycode == 65307)
		closewin(info);
/*	if (keycode == 65361)
		turn_left(info);
	if (keycode == 65363)
		turn_right(info);
	if (keycode == 65362)
		mv_for(info);
	if (keycode == 65364)
		mv_back(info);
	if (keycode == 97)
		mv_left(info);
	if (keycode == 100)
		mv_right(info);
	if (keycode == 119)
		mv_for(info);
	if (keycode == 115)
		mv_back(info);
	tracing_again(info);*/
	looping_hook(info);
	return (0);
}

int	hook_release(int keycode, t_info *info)
{
	printf("Keycode release : %d\n", keycode);
	if (keycode == 65361)
		info->hook.cam_left = 0;
	if (keycode == 65363)
		info->hook.cam_right = 0;
	if (keycode == 65362)
		info->hook.forward2 = 0;
	if (keycode == 65364)
		info->hook.backward2 = 0;
	if (keycode == 97)
		info->hook.left = 0;
	if (keycode == 100)
		info->hook.right = 0;
	if (keycode == 119)
		info->hook.forward = 0;
	if (keycode == 115)
		info->hook.backward = 0;
	looping_hook(info);
	return (0);
}

int	looping_hook(t_info *info)
{
	if (info->hook.cam_left && !info->hook.cam_right)
		turn_left(info);
	if (info->hook.cam_right && !info->hook.cam_left)
		turn_right(info);
	if ((info->hook.forward || info->hook.forward2) && (!info->hook.backward || !info->hook.backward2))
		mv_for(info);
	if ((info->hook.backward || info->hook.backward2) && (!info->hook.forward || !info->hook.forward2))
		mv_back(info);
	if (info->hook.left && !info->hook.right)
		mv_left(info);
	if (info->hook.right && !info->hook.left)
		mv_right(info);
	tracing_again(info);
	return (0);
}
