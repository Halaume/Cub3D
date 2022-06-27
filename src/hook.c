/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:40:59 by ghanquer          #+#    #+#             */
/*   Updated: 2022/06/27 16:04:33 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	hook(int keycode, t_info *info)
{
	printf("Keycode : %d\n", keycode);
/*	if (keycode == 65307)
		closewin(info);
	if (keycode == 65361)
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
	return (0);
}

int	hook_release(int keycode, t_info *info)
{
}
