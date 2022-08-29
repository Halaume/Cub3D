/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:33:59 by ghanquer          #+#    #+#             */
/*   Updated: 2022/08/29 16:45:23 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/time.h>

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
	t_data				img;
	char				*path;
	int					height;
	int					width;
	int					index;
	struct s_texture	*next;
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
	int	mouse_hold;
	int	mouse_pos;
	int	mouse_prev_pos;
}	t_hooking;

typedef struct s_door {
	int				x;
	int				y;
	int				is_op;
	unsigned int	last_open;
	struct s_door	*next;
}	t_door;

typedef struct s_fold {
	char		*path;
	int			nb;
	t_texture	*sprite;
}	t_fold;

typedef struct s_info {
	struct timeval	start;
	t_player	player;
	t_hooking	hook;
	t_data		img;
	t_texture	*texture_n;
	t_texture	*texture_s;
	t_texture	*texture_w;
	t_texture	*texture_e;
	t_texture	*texture_d;
	t_texture	*texture_ex;
	t_map		*mapping;
	t_door		*door;
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
	int			s_m;
	int			print_map;
	int			is_exit;
}	t_info;

typedef struct s_casting {
	t_texture	texture;
	t_texture	texture_ex;
	double		delta[2];
	double		ray[2];
	double		exit_ray[2];
	double		exit_mid[2];
	double		exit_ends[4];
	double		curr[2];
	double		proj_screen[4];
	double		wall_height;
	double		ex_height;
	double		dir_v_x;
	double		dir_v_y;
	double		prev_x;
	double		prev_y;
	double		distance0;
	double		distance1;
	double		wall_ratio;
	double		percent;
	double		percent_ex;
	double		step;
	double		step_ex;
	double		current;
	double		exit[2];
	double		exit_dist;
	int			exit_state;
	int			percent_y;
	int			proj_dist;
	int			is_wall;
	int			start_px;
	int			end_px;
	int			start_px_ex;
	int			end_px_ex;
	int			side;
	char		*dist;
	char		*origin;
}	t_casting;


//	TEST

int						check_north_corner(t_info *info, t_casting *cast);
int						check_south_corner(t_info *info, t_casting *cast);
int						check_west_corner(t_info *info, t_casting *cast);
int						check_east_corner(t_info *info, t_casting *cast);

//	Main

int					ft_closewin(t_info *info, int err);
int					ft_init_window(t_info *info);

//	Cub3D Basics 1 && 2

int					ft_parsing_info_err(t_info *info);
t_hooking			init_hook(void);
void				init_texture(t_info *info);
void				init_info(t_info *info, char *file);

void				tracing_again(t_info *info);
void				my_mlx_pixel_put(t_data *data, int x, int y, int color);
int					closewin(t_info *info);

//			Door

t_door				*get_this_door(t_door *list, int x, int y);
void				open_door(t_info *info);
void				door_closed(t_info *info);
void				close_door(t_info *info, t_door *door);

//			Hooking

//hook.c
int					hook(int keycode, t_info *info);
int					hook_release(int keycode, t_info *info);
void				mouse_loop(t_info *info);
int					looping_hook(t_info *info);
//hook_mouse.c
int					hook_mouse(int keycode, int x, int y, t_info *info);
int					hook_mouse_release(int keycode, int x, int y, t_info *info);
int					hook_mouse_mouv(int x, int y, t_info *info);

/*--------------------PARSING-------------------*/
//			Parse
int					ft_check_map(char *buf);
int					ft_play(t_info *info, char *buf);
int					ft_parsarg(t_info *info);
int					ft_init_fd(t_info *info, char *file);
int					ft_parse(t_info *info, char *file);
//			Colors
int					create_trgb(int t, int r, int g, int b);
int					ft_check_colors(char **tab);
int					ft_fill_color(int *tofill, char *buf);
//			Coloring
void				ft_player_color(int rgb[3]);
void				ft_wall_color(int rgb[3]);
void				ft_space_color(int rgb[3]);
void				ft_door_color(int rgb[3]);
void				ft_floor_color(int rgb[3]);
void				ft_exit_color(int rgb[3]);
//			Map
void				ft_mapadd_back(t_map **map, t_map *new);
int					ft_mapnew(t_map **map, char *buf);
size_t				ft_maplen(t_map *chain);
size_t				ft_longest(t_map *map);
int					ft_getmap(t_info *info);
//			Check Map
int					ft_charcheck(t_info *info, char **map, int y, int x);
int					ft_parsingage(t_info *info);
int					ft_check_doex(t_info *info);
int					ft_valid_map(t_info *info);
//			Player
int					ft_nb_player(char **map);
void				ft_init_player_angle(t_info *info, int y, int x);
int					new_init_player(t_info *info);
//			Check Map_tools
int					ft_valid_elems(char c);
int					ft_check_around(char **map, int y, int x);
int					ft_check_zero(char **map, int y, int x);
int					ft_checkside(char c);
int					ft_sides(char **map);
//			Textures (partext)
void				ft_spriteadd_back(t_texture **sprite, t_texture *new);
int					ft_sprite_new(t_texture **text, char *path, int i);
int					ft_text_new(t_info *info, t_texture **text, char *path);
int					ft_fill_sprite(t_texture **text, char *path, int nb);
int					ft_init_sprite(t_info *info, t_texture **text, char *path);
int					ft_fill_text(t_texture *text, char *buf);
int					ft_add_text(t_info *info, char *buf, int err);
int					ft_check_fill(char *buf);

//			Casting

void				get_proj_screen(t_info *info, t_casting *cast);
void				next_curr(t_casting *cast, int side);
void				choose_texture(t_info *info, t_casting *cast);
void				do_it_pls(t_info *info, t_casting *cast, int i);
void				get_the_wall(t_info *info, t_casting *cast, int i);
void				check_angle(t_info *info, t_casting *cast);
void				get_the_exit(t_info *info, t_casting *cast, int i);
void				cast_droit(t_info *info, t_casting *cast);
void				cast_angle(t_info *info, t_casting *cast);
void				casting2(t_info *info, t_casting *cast, int i);
void				brice_casting(t_info *info);

//			Player Mouvement

void				mv_left(t_info *info);
void				mv_right(t_info *info);
void				mv_for(t_info *info);
void				mv_back(t_info *info);
void				turn_right(t_info *info);
void				turn_left(t_info *info);
int					is_wall(t_info *info, double y, double x);

//			Doors

int					ft_count_walldo(char **map, int y, int x, int *i);
int					ft_check_doors(char **map, int y, int x);
int					ft_fill_doors(t_info *info, int x, int y);
int					ft_doors(t_info *info, int i);

//			Texture

void				get_address(t_info *info);
int					get_texture(t_info *info);

//			Affichage

void				put_the_wall(t_info *info, t_casting *cast, int *i);
void				put_col(t_info *info, t_casting *casting, int y);

//			Minimap
void				ft_init_color_minimap(t_info *info, int pos[2], int rgb[3]);
int					ft_fill_minimap(t_info *info, int x, int y, int pos[2]);
int					ft_launch_minimap(t_info *info);
void				ft_mapping(t_info *info);

//			Print_map
int					ft_print_map(t_info *info, int x, int y, int rgb[3]);
void				ft_init_color_map(t_info *info, int ij[2], int rgb[3]);
void				ft_draw_map(t_info *info);
void				ft_map(t_info *info);

//			Liberation

void				free_char_char(char **str);
void				ft_free(t_info *info);
//void				free_func(t_info *info);
void				ft_free_doors(t_door *doors);

//			GNL
	
unsigned int		ft_test_line(char *str);
char				*ft_fill_str(char *str, char *buf);
char				*get_line(char *str, int fd);
char				*get_next_line(int fd);

//			Tools
int					ft_poserr(int y, int x, char *str);
int					ft_putstr_error(char *error);
int					ft_putstr_frror(char *error, char *str, int i);
int					ft_perror(char *error, char *str);
int					ft_perror_free(char *error, char *str, int i);
unsigned long long	get_now(t_info *info);

//			PRINT A ENLEVER

void			ft_print_mapping(t_map *map);
void			ft_print_text(t_info *info);
void			print_tab(char **tab);
void			print_doors(t_door *door);

#endif
