#include "../inc/cub3d.h"

int	ft_print_map(t_info *info, int x, int y, int rgb[3])
{
	int	i;
	int	j;

	i = -1;
	while (++i < 20)
	{
		j = -1;
		while (++j < 20)
			my_mlx_pixel_put(&info->img, x + j, y + i, create_trgb(100,
					rgb[0], rgb[1], rgb[2]));
	}
	return (0);
}

void	ft_init_color_map(t_info *info, int ij[2], int rgb[3])
{
	if (ij[1] == (int) info->player.x && ij[0] == (int) info->player.y)
		ft_player_color(rgb);
	else if (info->map[ij[0]][ij[1]] == ' ')
		ft_space_color(rgb);
	else if (info->map[ij[0]][ij[1]] == '1')
		ft_wall_color(rgb);
	else if (info->map[ij[0]][ij[1]] == '2')
		ft_door_color(rgb);
	else
		ft_floor_color(rgb);
}

void	ft_draw_map(t_info *info)
{
	int	x;
	int	y;
	int	ij[2];
	int	rgb[3];

	ij[0] = 0;
	y = 10;
	while (info->map[ij[0]])
	{
		ij[1] = 0;
		x = 10;
		while (info->map[ij[0]][ij[1]])
		{
			ft_init_color_map(info, ij, rgb);
			ft_print_map(info, x, y, rgb);
			x += 20;
			ij[1] += 1;
		}
		y += 20;
		ij[0] += 1;
	}
}

int	ft_open_map(t_info *info)
{
	mlx_destroy_image(info->mlx, info->img.img);
	info->img.img = mlx_new_image(info->mlx, info->nb_col * 20 + 20, \
			info->nb_line * 20 + 20);
	if (!info->img.img)
	{
		ft_closewin(info, 1);
		ft_putstr_error("Error\nImage issue\n");
		exit(1);
	}
	info->img.addr = mlx_get_data_addr(info->img.img, \
			&info->img.bits_per_pixel, &info->img.line_length, \
			&info->img.endian);
	if (!info->img.addr)
	{
		ft_closewin(info, 1);
		ft_putstr_error("Error\nImage address issue\n");
		exit(1);
	}
	ft_draw_map(info);
	mlx_put_image_to_window(info->mlx, info->window, info->img.img, 0, 0);
	return (1);
}

void	ft_map(t_info *info)
{
	if (info->nb_col > 94 || info->nb_line > 52)
	{
		ft_putstr_error("Error\nCan't print this huge map\n");
		return ;
	}
	if (!info->print_map)
		info->print_map = ft_open_map(info);
	else
		info->print_map = 0;
}
