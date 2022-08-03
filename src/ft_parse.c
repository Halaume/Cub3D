/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:19:06 by nflan             #+#    #+#             */
/*   Updated: 2022/08/03 17:49:48 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_fill_text(t_texture *text, char *buf)
{
	if (text->path)
		return (2);
	text->path = ft_strtrim(buf, " \n");
	if (!text->path)
		return (1);
//	text->width = 100;
//	text->height = 100;
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

void	ft_mapadd_back(t_map **map, t_map *new)
{
	t_map	*tmp;

	tmp = *map;
	if (map && new)
	{
		if (*map == NULL)
			*map = new;
		else
		{
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
	}
}

int	ft_mapnew(t_map **map, char *buf)
{
	t_map	*new;

	new = ft_calloc(sizeof(t_map), 1);
	if (!new)
		return (ft_putstr_error("Error\nMalloc error\n"));
	new->line = ft_strtrim(buf, "\n");
	if (!new->line)
		return (free(new), ft_putstr_error("Error\nMalloc error\n"));
	ft_mapadd_back(map, new);
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
			return (ft_putstr_error("Error\nIl ne doit rien y avoir apres la ma\
p\n"));
		if (ft_mapnew(&info->mapping, buf))
			return (1);
		id = 7;
	}
	if (!ft_check_map(buf) && id == 7)
		id = 8;
	return (0);
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
	if (!info->texture_n.path || !info->texture_s.path || !info->texture_w.path
		|| !info->texture_e.path || !info->color_sky || !info->color_floor)
		return (ft_putstr_error("Error\nIl manque des informations\n"));
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
	if (ft_getmap(info))
		return (ft_free(info), 1);
	ft_print_text(info);
//	ft_free(info);
//	exit(0);
	return (0);
}
