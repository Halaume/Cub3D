/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:19:06 by nflan             #+#    #+#             */
/*   Updated: 2022/08/04 16:06:15 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
	if (ft_valid_map(info))
		return (ft_free(info), 1);
//	ft_free(info);
//	exit(0);
	return (0);
}
