/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:31:27 by ghanquer          #+#    #+#             */
/*   Updated: 2022/08/23 11:11:31 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

int	ft_closewin(t_info *info, int err)
{
	if (info->window)
	{
		if (info->img.img)
			mlx_destroy_image(info->mlx, info->img.img);
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
	return (err);
}

int	ft_init_window(t_info *info)
{
	info->mlx = mlx_init();
	if (!info->mlx)
		return (ft_closewin(info, 1));
	info->window = mlx_new_window(info->mlx, info->w, info->h, "Cub3D");
	if (!info->window)
		return (ft_closewin(info, 1));
	info->img.img = mlx_new_image(info->mlx, info->w, info->h);
	if (!info->img.img)
		return (ft_closewin(info, 1));
	info->img.addr = mlx_get_data_addr(info->img.img, &info->img.bits_per_pixel,
			&info->img.line_length, &info->img.endian);
	if (!info->img.addr)
		return (ft_closewin(info, 1));
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc != 2)
		return (ft_putstr_error("Error\nNombre d'arguments invalide\n"));
	init_info(&info, argv[1]);
	if (ft_init_window(&info))
		return (ft_putstr_error("Error\nInitialisation de la MLX echouee\n"));
	if (get_texture(&info))
	{
		ft_closewin(&info, 1);
		exit (1);
	}
	brice_casting(&info);
	mlx_do_key_autorepeatoff(info.mlx);
	mlx_hook(info.window, 17, 0, closewin, &info);
	mlx_hook(info.window, 2, 1L << 0, hook, &info);
	mlx_hook(info.window, 3, 1L << 1, hook_release, &info);
	mlx_hook(info.window, 4, 1L << 2, hook_mouse, &info);
	mlx_hook(info.window, 5, 1L << 3, hook_mouse_release, &info);
	mlx_hook(info.window, 6, 1L << 6, hook_mouse_mouv, &info);
	mlx_loop_hook(info.mlx, looping_hook, &info);
	mlx_loop(info.mlx);
	return (0);
}
