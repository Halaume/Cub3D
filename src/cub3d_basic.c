/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_basic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:38:59 by ghanquer          #+#    #+#             */
/*   Updated: 2022/08/03 13:15:07 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_player	new_init_player(void)
{
	t_player	player;

	player.x = 5;
	player.y = 5;
	player.angle = M_PI / 2;
	return (player);
}

t_hooking	init_hook(void)
{
	t_hooking	my_hook;

	my_hook.forward = 0;
	my_hook.forward2 = 0;
	my_hook.backward = 0;
	my_hook.backward2 = 0;
	my_hook.left = 0;
	my_hook.right = 0;
	my_hook.cam_left = 0;
	my_hook.cam_right = 0;
	return (my_hook);
}

int	ft_fill_text(t_texture *text, char *buf)
{
	if (text->path)
		return (2);
	text->path = ft_strtrim(buf, " \n");
	if (!text->path)
		return (1);
	return (0);
}

int	ft_add_text(t_info *info, char *buf)
{
	int	err;

	err = 0;
	if (!strncmp(buf, "NO ", 3))
		err = ft_fill_text(&info->texture_n, buf + 2);
	else if (!strncmp(buf, "SO ", 3))
		err = ft_fill_text(&info->texture_s, buf + 2);
	else if (!strncmp(buf, "WE ", 3))
		err = ft_fill_text(&info->texture_w, buf + 2);
	else if (!strncmp(buf, "EA ", 3))
		err = ft_fill_text(&info->texture_e, buf + 2);
	else if (!strncmp(buf, "F ", 2))
		err = ft_fill_color(&info->color_floor, buf + 1);
	else if (!strncmp(buf, "C ", 2))
		err = ft_fill_color(&info->color_sky, buf + 1);
	if (err == 1)
		return (ft_putstr_error("Error\nMalloc error\n"));
	else if (err == 2)
		return (ft_putstr_error("Error\nDoublon dans les textures\n"));
	else if (err == 3)
		return (ft_putstr_error("Error\nLa couleur n'est pas bonne Kevin\n"));
	return (0);
}

int	ft_check_fill(char *buf)
{
	int	l;

	l = ft_strlen(buf);
	if (!l)
		return (0);
	if (ft_strnstr(buf, "NO", l) || ft_strnstr(buf, "SO", l)
		|| ft_strnstr(buf, "WE", l) || ft_strnstr(buf, "EA", l)
		|| ft_strnstr(buf, "F", l) || ft_strnstr(buf, "C", l))
		return (1);
	return (0);
}

int	ft_check_map(char *buf)
{
	if (*buf)
		while (*buf == ' ' || *buf == '\n')
			buf++;
	if (*buf)
		return (1);
	return (0);
}

//id == 6 veut dire qu'on a toutes les infos donc il manque la map
//id == 7 veut dire qu'on a commence a parser la carte
//id == 8 veut dire qu'on a termine de parser la carte (ligne vide)
//donc si on croise une ligne de map alors qu'on avait termine, erreur
int	ft_play(t_info *info, char *buf)
{
	static int	id = 0;

	if (id < 6 && ft_check_fill(buf))
	{
		while (*buf == ' ')
			buf++;
		if (ft_add_text(info, buf))
			return (1);
		id++;
	}
	else if (id >= 6 && ft_check_map(buf))
	{
		if (id == 8)
			return (ft_putstr_error("Error\nLigne vide dans la map\n"));
	}
	if (!ft_check_map(buf) && id == 7)
		id = 8;
	return (0);
}

void	ft_print_text(t_info *info)
{
	if (info)
	{
		printf("Path text_n = '%s'\n", info->texture_n.path);
		printf("Path text_s = '%s'\n", info->texture_s.path);
		printf("Path text_w = '%s'\n", info->texture_w.path);
		printf("Path text_e = '%s'\n", info->texture_e.path);
		printf("Floor color = '%d'\n", info->color_floor);
		printf("Celling color = '%d'\n", info->color_sky);
	}
}

int	ft_parsarg(t_info *info)
{
	char	*buf;

	buf = get_next_line(info->fd);
	if (!buf)
		return (ft_putstr_error("Error\nMalloc error\n"));
	while (buf)
	{
		if (ft_play(info, buf))
			return (free(buf), 1);
		free(buf);
		buf = get_next_line(info->fd);
	}
	ft_print_text(info);
	return (0);
}

int	ft_parse(t_info *info, char *file)
{
	info->fd = open(file, O_RDONLY);
	if (info->fd == -1)
		return (ft_perror("Error\nOuverture de map echouee", NULL));
	if (ft_parsarg(info))
		return (ft_free(info), 1);
	close(info->fd);
	info->fd = 0;
	return (0);
}

void	init_info(t_info *info, char *file)
{
	info->player = new_init_player();
	info->h = 1080;
	info->w = 1920;
	info->fd = 0;
	info->mlx = NULL;
	info->window = NULL;
	info->color_sky = 0;
	info->color_floor = 0;
	info->nb_line = 9;
	info->nb_col = 9;
	info->hook = init_hook();
	info->texture_n.img.img = NULL;
	info->texture_s.img.img = NULL;
	info->texture_e.img.img = NULL;
	info->texture_w.img.img = NULL;
	info->texture_n.path = NULL;
	info->texture_s.path = NULL;
	info->texture_e.path = NULL;
	info->texture_w.path = NULL;
	info->img.img = NULL;
	info->img.addr = NULL;
	info->map = NULL;
	info->mapping = NULL;
	if (ft_parse(info, file))
		exit (1);
}
