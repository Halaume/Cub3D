/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_partext_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:48:39 by nflan             #+#    #+#             */
/*   Updated: 2022/08/26 15:09:00 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

void	ft_spriteadd_back(t_texture **sprite, t_texture *new)
{
	t_texture	*tmp;

	tmp = *sprite;
	if (sprite && new)
	{
		if (*sprite == NULL)
			*sprite = new;
		else
		{
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
	}
}

int	ft_sprite_new(t_texture *text, char *path, int i)
{
	t_texture	*new;

	new = ft_calloc(sizeof(t_texture), 1);
	if (!new)
		return (ft_putstr_error("Error\nMalloc error"));
	new->path = ft_strdup(path);
	new->index = i;
	ft_spriteadd_back(&text, new);
	return (0);
}

int	ft_fill_sprite(t_texture *text, char *path, int nb)
{
	int		i;

	i = -1;
	while (++i < nb)
	{
		path = ft_strjoin_free(path, "/", 1);
		if (!path)
			return (ft_putstr_error("Error\nMalloc error\n"));
		path = ft_strjoiiin_free(path, ft_itoa(i), ".xpm", 4);
		if (!path)
			return (ft_putstr_error("Error\nMalloc error\n"));
		if (ft_sprite_new(text, path, i))
			return (ft_putstr_error("Error\nMalloc error\n"));
		free(path);
		path = NULL;
	}
	return (0);
}

int	ft_init_sprite(t_info *info, t_texture *text, char *path)
{
	int				i;
	DIR				*fd;
	struct dirent	*dir;
	t_texture		*tmp;

	fd = 0;
	i = 0;
	if (!path)
		return (0);
	fd = opendir(path);
	if (!fd)
		return (ft_perror("Error\n", path));
	while (1)
	{
		dir = readdir(fd);
		if (!dir)
			break ;
		i++;
	}
	if (ft_fill_sprite(text, path, i))
		return (1);
	tmp = text;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = text;
	closedir(fd);
	return (0);
}

int	ft_text_new(t_info *info, t_texture *text, char *buf)
{
	if (text)
		return (2);
	if (!ft_strnstr(buf, ".xpm", ft_strlen(buf)))
		return (ft_init_sprite(info, text, buf));
	else
	{
		text = ft_calloc(sizeof(t_texture), 1);
		if (!text)
			return (ft_putstr_error("Error\nMalloc error"));
		text->path = ft_strtrim(buf, " \n");
		if (!text->path)
			return (ft_putstr_error("Error\nMalloc error"));
		text = 0;
	}
	return (0);
}

/*int	ft_fill_fold(t_fold *fold, char *buf)
{
	if (fold->path)
		return (2);
	fold->path = ft_strtrim(buf, " \n");
	if (!fold->path)
		return (ft_putstr_error("Error\nMalloc error"));
	return (0);
}*/

int	ft_add_text(t_info *info, char *buf, int err)
{
	if (!strncmp(buf, "NO ", 3))
		err = ft_text_new(info, info->texture_n, buf + 2);
	else if (!strncmp(buf, "SO ", 3))
		err = ft_text_new(info, info->texture_s, buf + 2);
	else if (!strncmp(buf, "WE ", 3))
		err = ft_text_new(info, info->texture_w, buf + 2);
	else if (!strncmp(buf, "EA ", 3))
		err = ft_text_new(info, info->texture_e, buf + 2);
	else if (!strncmp(buf, "DO ", 3))
		err = ft_text_new(info, info->texture_d, buf + 2);
	else if (!strncmp(buf, "EX ", 3))
		err = ft_text_new(info, info->texture_ex, buf + 2);
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
	if (!buf || l == 1)
		return (0);
	if (ft_strnstr(buf, "NO ", l) || ft_strnstr(buf, "SO ", l)
		|| ft_strnstr(buf, "WE ", l) || ft_strnstr(buf, "EA ", l)
		|| ft_strnstr(buf, "F ", l) || ft_strnstr(buf, "C ", l)
		|| ft_strnstr(buf, "DO ", l) || ft_strnstr(buf, "EX ", l))
		return (1);
	while (*buf == ' ')
		buf++;
	if (*buf != '1')
		return (2);
	return (0);
}
