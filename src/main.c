/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:31:27 by ghanquer          #+#    #+#             */
/*   Updated: 2022/06/27 16:05:07 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc != 2)
		return (printf("Error\nNombre d'arguments invalide\n"), 1);
	init_info(&info);
	info.fd = open(argv[1], O_RDONLY);
	if (!info.fd)
		return (printf("Error\nOuverture de map echouee\n"), 1);
	info.mlx = mlx_init();
	info.window = mlx_new_window(info.mlx, 1920, 1080, "Cub3D");
	info.img.img = mlx_new_image(info.mlx, 1920, 1080);
	info.img.addr = mlx_get_data_addr(info.img.img, &info.img.bits_per_pixel, \
			&info.img.line_length, &info.img.endian);
	//do_stuff
	info.map = get_map(info.fd);
	brice_casting(&info);
	//print
	mlx_hook(info.window, 17, 0, closewin, &info);
	mlx_hook(info.window, 2, 1L << 0, hook, &info);
	mlx_hook(info.window, 2, 1L << 1, hook_release, &info);
	mlx_loop_hook(info.window, looping_hook, &info);
	mlx_loop(info.mlx);
	return (0);
}
