/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_partext_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:48:39 by nflan             #+#    #+#             */
/*   Updated: 2022/09/01 11:22:53 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

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
	return (0);
}

int	ft_init_sprite(t_texture **text, char *path, DIR *fd)
{
	int				i;
	struct dirent	*dir;
	t_texture		*tmp;

	i = 0;
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
	return (0);
}

int	ft_text_new(t_texture **text, char *buf)
{
	char		*path;
	DIR			*fd;
	struct stat	state;

	if (*text)
		return (2);
	path = ft_strtrim(buf, " \n");
	if (!path)
		return (ft_putstr_error("Error\nMalloc error\n"));
	if (stat(path, &state))
		return (ft_perror("Error\nTexture: ", path), free(path), 1);
	if (S_ISDIR(state.st_mode))
	{
		fd = opendir(path);
		if (!fd)
			return (ft_perror("Error\nTexture: ", path), free(path), 1);
		if (ft_init_sprite(text, path, fd))
			return (free(path), closedir(fd), 1);
		closedir(fd);
	}
	else
		if (ft_sprite_new(text, path, 0))
			return (free(path), ft_putstr_error("Error\nMalloc error\n"));
	free(path);
	return (0);
}

int	ft_add_text(t_info *info, char *buf, int err)
{
	if (!strncmp(buf, "NO ", 3))
		err = ft_text_new(&info->texture_n, buf + 2);
	else if (!strncmp(buf, "SO ", 3))
		err = ft_text_new(&info->texture_s, buf + 2);
	else if (!strncmp(buf, "WE ", 3))
		err = ft_text_new(&info->texture_w, buf + 2);
	else if (!strncmp(buf, "EA ", 3))
		err = ft_text_new(&info->texture_e, buf + 2);
	else if (!strncmp(buf, "DO ", 3))
		err = ft_text_new(&info->texture_d, buf + 2);
	else if (!strncmp(buf, "EX ", 3))
		err = ft_text_new(&info->texture_ex, buf + 2);
	else if (!strncmp(buf, "F ", 2))
		err = ft_fill_color(&info->color_floor, buf + 1);
	else if (!strncmp(buf, "C ", 2))
		err = ft_fill_color(&info->color_sky, buf + 1);
	if (err == 1)
		return (err);
	else if (err == 2)
		return (ft_putstr_error("Error\nDuplicate texture\n"));
	else if (err == 3)
		return (ft_putstr_error("Error\nWrong RGB color (255,255,255 max)\n"));
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
