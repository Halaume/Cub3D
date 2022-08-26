/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_partext_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:48:39 by nflan             #+#    #+#             */
/*   Updated: 2022/08/26 15:03:16 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

int	ft_fill_text(t_texture *text, char *buf)
{
	if (text->path)
		return (2);
	text->path = ft_strtrim(buf, " \n");
	if (!text->path)
		return (1);
	return (0);
}

int	ft_fill_fold(t_fold *fold, char *buf)
{
	if (fold->path)
		return (2);
	fold->path = ft_strtrim(buf, " \n");
	if (!fold->path)
		return (1);
	return (0);
}

int	ft_add_text(t_info *info, char *buf, int err)
{
	if (!strncmp(buf, "NO ", 3))
		err = ft_fill_text(&info->texture_n, buf + 2);
	else if (!strncmp(buf, "SO ", 3))
		err = ft_fill_text(&info->texture_s, buf + 2);
	else if (!strncmp(buf, "WE ", 3))
		err = ft_fill_text(&info->texture_w, buf + 2);
	else if (!strncmp(buf, "EA ", 3))
		err = ft_fill_text(&info->texture_e, buf + 2);
	else if (!strncmp(buf, "DO ", 3))
		err = ft_fill_text(&info->texture_d, buf + 2);
	else if (!strncmp(buf, "EX ", 3))
		err = ft_fill_fold(&info->fold_ex, buf + 2);
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
