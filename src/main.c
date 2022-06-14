/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:31:27 by ghanquer          #+#    #+#             */
/*   Updated: 2022/06/14 14:59:14 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	main(int argc, char **argv)
{
	t_info	info;
	(void)argv;

	if (argc != 2)
		return (printf("Error\nNombre d'arguments invalide\n"), 1);
	init_info(&info);
	info.mlx = mlx_init();
	info.window = mlx_new_window(info.mlx, 1920, 1080, "Cub3D");
	info.img.img = mlx_new_image(info.mlx, 1920, 1080);
	info.img.addr = mlx_get_data_addr(info.img.img, &info.img.bits_per_pixel, \
			&info.img.line_length, &info.img.endian);
	mlx_hook(info.window, 17, 0, closewin, &info);
	mlx_hook(info.window, 2, 1L << 0, hook, &info);
	mlx_loop(info.mlx);
	return (0);
}
