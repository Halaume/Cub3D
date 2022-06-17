/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:33:59 by ghanquer          #+#    #+#             */
/*   Updated: 2022/06/17 17:59:31 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>

# define WIDTH 1920
# define HEIGHT 1080
# define BUFFER_SIZE 1

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct	s_info {
	void	*mlx;
	void	*window;
	t_data	img;
	int		h;
	int		w;
	int		fd;
	char	**map;
	double	my_pos_x;
	double	my_pos_y;
	double	dir_x;
	double	dir_y;
	double	view_x;
	double	view_y;
	int		color_sky;
	int		color_floor;
}	t_info;

typedef struct	s_casting {
	double	ray_pos_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	int		is_wall;
	int		go_x;
	int		go_y;
	double	next_x;
	double	next_y;
	double	delta_dir_x;
	double	delta_dir_y;
	double	wall_start;
	double	wall_end;
	double	perp_dist;
	int		case_x;
	int		case_y;
	int		side;
	int		line_h;
}	t_casting;

//			Basics

int		ft_strlen(char *str);
void	init_info(t_info *info);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		closewin(t_info *info);
int		hook(int keycode, t_info *info);

//			Map

char	**get_map(int fd);

//			Casting

void	casting(t_info *info);
void	brice_casting(t_info *info);

//			Liberation

void	free_func(t_info *info);
void	free_char_char(char **str);

//			Affichage

void	put_col(t_info *info, int wh, int y);

//			GNL

int		check_line(char *str);
int		fill_line(char *line, char *buffer, int j, int i);
char	*ft_join(char *line, char *buffer);
char	*get_line(int fd, char *line);
char	*del_start(char *line);
char	*get_start(char *line);
char	*get_next_line(int fd);

#endif
