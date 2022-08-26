/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_partext_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:48:39 by nflan             #+#    #+#             */
/*   Updated: 2022/08/26 17:15:30 by nflan            ###   ########.fr       */
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

int	ft_sprite_new(t_texture **text, char *path, int i)
{
	t_texture	*new;

	new = ft_calloc(sizeof(t_texture), 1);
	if (!new)
		return (ft_putstr_error("Error\nMalloc error"));
	new->path = ft_strdup(path);
	new->index = i;
	ft_spriteadd_back(text, new);
	return (0);
}

int	ft_fill_sprite(t_texture **text, char *path, int nb)
{
	int		i;
	char	*tmp;

	i = -1;
	while (++i < nb - 2)
	{
		tmp = ft_strjoin(path, "/");
		if (!tmp)
			return (ft_putstr_error("Error\nMalloc error\n"));
		tmp = ft_strjoiiin_free(tmp, ft_itoa(i), ".xpm", 4);
		if (!tmp)
			return (ft_putstr_error("Error\nMalloc error\n"));
		if (ft_sprite_new(text, tmp, i))
			return (ft_putstr_error("Error\nMalloc error\n"));
		free(tmp);
		tmp = NULL;
	}
	free(path);
	return (0);
}

int	ft_init_sprite(t_info *info, t_texture **text, char *path)
{
	int				i;
	DIR				*fd;
	struct dirent	*dir;
	t_texture		*tmp;

(void) info;
	fd = 0;
	i = 0;
	fd = opendir(path);
	if (!fd)
		return (ft_perror("Error\nTexture: ", path));
	while (1)
	{
		dir = readdir(fd);
		if (!dir)
			break ;
		i++;
	}
	if (ft_fill_sprite(text, path, i))
		return (1);
	if (*text && (*text)->next)
	{
		tmp = *text;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = *text;
	}
	closedir(fd);
	return (0);
}

int	ft_text_new(t_info *info, t_texture **text, char *buf)
{
	char	*path;

	if (*text)
		return (2);
	path = ft_strtrim(buf, " \n");
	if (!path)
		return (ft_putstr_error("Error\nMalloc error\n"));
	if (ft_strncmp(path + ft_strlen(path) - 4, ".xpm", 5))
		return (ft_init_sprite(info, text, path));
	else
		if (ft_sprite_new(text, path, 0))
			return (ft_putstr_error("Error\nMalloc error\n"));
	free(path);
	return (0);
}

int	ft_add_text(t_info *info, char *buf, int err)
{
	if (!strncmp(buf, "NO ", 3))
		err = ft_text_new(info, &info->texture_n, buf + 2);
	else if (!strncmp(buf, "SO ", 3))
		err = ft_text_new(info, &info->texture_s, buf + 2);
	else if (!strncmp(buf, "WE ", 3))
		err = ft_text_new(info, &info->texture_w, buf + 2);
	else if (!strncmp(buf, "EA ", 3))
		err = ft_text_new(info, &info->texture_e, buf + 2);
	else if (!strncmp(buf, "DO ", 3))
		err = ft_text_new(info, &info->texture_d, buf + 2);
	else if (!strncmp(buf, "EX ", 3))
		err = ft_text_new(info, &info->texture_ex, buf + 2);
	else if (!strncmp(buf, "F ", 2))
		err = ft_fill_color(&info->color_floor, buf + 1);
	else if (!strncmp(buf, "C ", 2))
		err = ft_fill_color(&info->color_sky, buf + 1);
	if (err == 1)
		return (err);
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
