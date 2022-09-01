/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:31:27 by ghanquer          #+#    #+#             */
/*   Updated: 2022/09/01 11:54:08 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_closewin(t_info *info, int err)
{
	if (info->window)
	{
		while (--info->nb_i >= 0)
		{
			if (info->img[info->nb_i].img)
				mlx_destroy_image(info->mlx, info->img[info->nb_i].img);
		}
		mlx_clear_window(info->mlx, info->window);
		mlx_destroy_window(info->mlx, info->window);
	}
	free_func(info);
	if (info->mlx)
	{
		mlx_do_key_autorepeaton(info->mlx);
		mlx_destroy_display(info->mlx);
		free(info->mlx);
	}
	if (err != 1)
		exit (0);
	exit (err);
}

int	ft_init_window(t_info *info)
{
	info->mlx = mlx_init();
	if (!info->mlx)
		return (ft_closewin(info, 1));
	info->window = mlx_new_window(info->mlx, info->w, info->h, "Cub3D");
	if (!info->window)
		return (ft_closewin(info, 1));
	while (info->nb_i < NB_IMG)
	{
		info->nb_i++;
		info->img[info->nb_i - 1].img = NULL;
		info->img[info->nb_i - 1].addr = NULL;
		info->img[info->nb_i - 1].img = mlx_new_image(info->mlx, info->w,
				info->h);
		if (!info->img[info->nb_i - 1].img)
			return (ft_closewin(info, 1));
		info->img[info->nb_i - 1].addr = mlx_get_data_addr(info->img[info->nb_i
				- 1].img, &info->img[info->nb_i - 1].bits_per_pixel,
				&info->img[info->nb_i - 1].line_length,
				&info->img[info->nb_i - 1].endian);
		if (!info->img[info->nb_i - 1].addr)
			return (ft_closewin(info, 1));
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc != 2)
		return (ft_putstr_error("Error\nInvalid number of args\n"));
	init_info(&info, argv[1]);
	if (ft_init_window(&info))
		return (ft_putstr_error("Error\nMLX initialization error\n"));
	if (get_texture(&info))
		ft_closewin(&info, 1);
	brice_casting(&info);
	mlx_do_key_autorepeatoff(info.mlx);
	mlx_hook(info.window, 17, 0, ft_closewin, &info);
	mlx_hook(info.window, 2, 1L << 0, hook, &info);
	mlx_hook(info.window, 3, 1L << 1, hook_release, &info);
	mlx_loop_hook(info.mlx, looping_hook, &info);
	mlx_loop(info.mlx);
	return (0);
}
