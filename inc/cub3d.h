/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:33:59 by ghanquer          #+#    #+#             */
/*   Updated: 2022/07/05 17:11:58 by ghanquer         ###   ########.fr       */
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

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_texture {
	t_data	img;
	char	*path;
	int		height;
	int		width;
}	t_texture;

typedef struct s_player {
	double	x;
	double	y;
	double	angle;

}	t_player;

typedef struct s_hooking {
	int	forward;
	int	forward2;
	int	backward;
	int	backward2;
	int	left;
	int	right;
	int	cam_left;
	int	cam_right;
}	t_hooking;

typedef struct s_info {
	t_player	player;
	t_hooking	hook;
	t_data		img;
	t_texture	texture_n;
	t_texture	texture_s;
	t_texture	texture_e;
	t_texture	texture_w;
	char		**map;
	void		*mlx;
	void		*window;
	int			h;
	int			w;
	int			fd;
	int			color_sky;
	int			color_floor;
	int			nb_line;
	int			nb_col;
}	t_info;

typedef struct s_casting {
	t_texture	texture;
	double		delta[2];
	double		ray[2];
	double		curr[2];
	double		proj_screen[4];
	double		wall_height;
	double		dir_v_x;
	double		dir_v_y;
	double		prev_x;
	double		prev_y;
	double		distance0;
	double		distance1;
	double		wall_ratio;
	double		percent;
	int			proj_dist;
	int			is_wall;
	int			start_px;
	int			end_px;
	int			side;
	char		*dist;
	char		*origin;
}	t_casting;

//			Basics

int		ft_strlen(char *str);
void	init_info(t_info *info);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		closewin(t_info *info);

//			Hooking

int		hook(int keycode, t_info *info);
int		hook_release(int keycode, t_info *info);
int		looping_hook(t_info *info);

//			Map

char	**get_map(int fd);

//			Casting

void	brice_casting(t_info *info);

//			Player Mouvement

void	mv_left(t_info *info);
void	mv_right(t_info *info);
void	mv_for(t_info *info);
void	mv_back(t_info *info);
void	turn_right(t_info *info);
void	turn_left(t_info *info);

//			Texture

int		get_texture(t_info *info);

//			Affichage

void	put_col(t_info *info, t_casting *casting, int y);
void	tracing_again(t_info *info);

//			Liberation

void	free_func(t_info *info);
void	free_char_char(char **str);

//			GNL

int		check_line(char *str);
int		fill_line(char *line, char *buffer, int j, int i);
char	*ft_join(char *line, char *buffer);
char	*get_line(int fd, char *line);
char	*del_start(char *line);
char	*get_start(char *line);
char	*get_next_line(int fd);

#endif
