/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:33:59 by ghanquer          #+#    #+#             */
/*   Updated: 2022/08/09 12:06:38 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>

# define WIDTH 1920
# define HEIGHT 1080

typedef struct s_map {
	char			*line;
	struct s_map	*next;
}	t_map;

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
	t_texture	texture_w;
	t_texture	texture_e;
	t_map		*mapping;
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
	double		step;
	double		current;
	int			percent_y;
	int			proj_dist;
	int			is_wall;
	int			start_px;
	int			end_px;
	int			side;
	char		*dist;
	char		*origin;
}	t_casting;

//			Basics

void			init_texture(t_info *info);
void			init_info(t_info *info, char *file);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
int				closewin(t_info *info);

//			Hooking

int				hook(int keycode, t_info *info);
int				hook_release(int keycode, t_info *info);
int				looping_hook(t_info *info);

/*--------------------PARSING-------------------*/
//			Parse
int				ft_check_map(char *buf);
int				ft_play(t_info *info, char *buf);
int				ft_parsarg(t_info *info);
int				ft_parse(t_info *info, char *file);
//			Colors
int				create_trgb(int t, int r, int g, int b);
int				ft_check_colors(char **tab);
int				ft_fill_color(int *tofill, char *buf);
//			Map
//char			**get_map(int fd);
void			ft_mapadd_back(t_map **map, t_map *new);
int				ft_mapnew(t_map **map, char *buf);
size_t			ft_maplen(t_map *chain);
size_t			ft_longest(t_map *map);
int				ft_getmap(t_info *info);
//			Check Map
int				ft_valid_map(t_info *info);
//			Player
int				ft_nb_player(char **map);
int				new_init_player(t_info *info);
//			Check Map_tools
int				ft_valid_elems(char c);
int				ft_check_around(char **map, int y, int x);
int				ft_check_zero(char **map, int y, int x);
int				ft_checkside(char c);
int				ft_sides(char **map);
//			Textures (partext)
int				ft_fill_text(t_texture *text, char *buf);
int				ft_add_text(t_info *info, char *buf);
int				ft_check_fill(char *buf);

//			Casting

void			brice_casting(t_info *info);
void			get_proj_screen(t_info *info, t_casting *cast);
void			next_curr(t_casting *cast, int side);
void			choose_texture(t_info *info, t_casting *cast);
void			do_it_pls(t_info *info, t_casting *cast, int i);
void			get_the_wall(t_info *info, t_casting *cast, int i);

//			Player Mouvement

void			mv_left(t_info *info);
void			mv_right(t_info *info);
void			mv_for(t_info *info);
void			mv_back(t_info *info);
void			turn_right(t_info *info);
void			turn_left(t_info *info);
int				is_wall(t_info *info, double y, double x);

//			Texture

int				get_texture(t_info *info);

//			Affichage

void			put_col(t_info *info, t_casting *casting, int y);
void			tracing_again(t_info *info);

//			Liberation

void			free_char_char(char **str);
void			ft_free(t_info *info);
void			free_func(t_info *info);

//			GNL

/*int		check_line(char *str);
int		fill_line(char *line, char *buffer, int j, int i);
char	*ft_join(char *line, char *buffer);
char	*get_line(int fd, char *line);
char	*del_start(char *line);
char	*get_start(char *line);*/
unsigned int	ft_test_line(char *str);
char			*ft_fill_str(char *str, char *buf);
char			*get_line(char *str, int fd);
char			*get_next_line(int fd);

//			Tools
int				ft_poserr(int y, int x, char *str);
int				ft_putstr_error(char *error);
int				ft_putstr_frror(char *error, char *str, int i);
int				ft_perror(char *error, char *str);
int				ft_perror_free(char *error, char *str, int i);

//			PRINT A ENLEVER

void	ft_print_mapping(t_map *map);
void	ft_print_text(t_info *info);
void	print_tab(char **tab);

#endif
