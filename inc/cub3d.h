/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:33:59 by ghanquer          #+#    #+#             */
/*   Updated: 2022/06/28 11:58:33 by ghanquer         ###   ########.fr       */
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

typedef struct	s_player {
	double	x;
	double	y;
	double	angle;

}	t_player;

typedef struct	s_hooking {
	int	forward;
	int	forward2;
	int	backward;
	int	backward2;
	int	left;
	int	right;
	int	cam_left;
	int	cam_right;
}	t_hooking;

typedef struct	s_info {
	t_player	player;
	t_hooking	hook;
	void		*mlx;
	void		*window;
	t_data		img;
	int			h;
	int			w;
	int			fd;
	char		**map;
	int			color_sky;
	int			color_floor;
	int			nb_line;
	int			nb_col;
}	t_info;

/*typedef struct	s_casting {
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
}	t_casting;*/

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

void	casting(t_info *info);
void	brice_casting(t_info *info);

//			Player Mouvement


void	mv_left(t_info *info);
void	mv_right(t_info *info);
void	mv_for(t_info *info);
void	mv_back(t_info *info);
void	turn_right(t_info *info);
void	turn_left(t_info *info);

//			Affichage

void	put_col(t_info *info, int wh, int oui, int y, double aled, double style);
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
