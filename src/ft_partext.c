/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_partext.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:48:39 by nflan             #+#    #+#             */
/*   Updated: 2022/08/05 12:23:48 by nflan            ###   ########.fr       */
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
	if (!l || l == 1)
		return (0);
	if (ft_strnstr(buf, "NO", l) || ft_strnstr(buf, "SO", l)
		|| ft_strnstr(buf, "WE", l) || ft_strnstr(buf, "EA", l)
		|| ft_strnstr(buf, "F", l) || ft_strnstr(buf, "C", l))
		return (1);
	else
		return (2);
	return (0);
}
