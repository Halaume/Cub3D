/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:19:06 by nflan             #+#    #+#             */
/*   Updated: 2022/08/26 15:09:52 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

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

	if (ft_check_fill(buf))
	{
		if (ft_check_fill(buf) == 2)
			return (ft_putstr_error("Error\nCaracteristique invalide\n"));
		while (*buf == ' ')
			buf++;
		if (ft_add_text(info, buf, 0))
			return (1);
	}
	else if (ft_check_map(buf))
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
	if (!info->texture_n || !info->texture_s || !info->texture_w
		|| !info->texture_e || !info->color_sky || !info->color_floor)
		return (ft_parsing_info_err(info));
	return (0);
}

int	ft_init_fd(t_info *info, char *file)
{
	char	*tmp;

	tmp = file + ft_strlen(file) - 4;
	if (ft_strncmp(tmp, ".cub", 5))
		return (ft_putstr_error("Error\nFichier invalide\n"));
	info->fd = open(file, O_RDONLY);
	if (info->fd == -1)
		return (ft_perror("Error\nOuverture de map echouee", NULL));
	return (0);
}

int	ft_parse(t_info *info, char *file)
{
	if (ft_init_fd(info, file))
		return (1);
	if (ft_parsarg(info))
		return (ft_free(info), 1);
	close(info->fd);
	info->fd = 0;
	if (ft_getmap(info))
		return (ft_free(info), 1);
	ft_print_text(info);
	if (ft_valid_map(info))
		return (ft_free(info), 1);
//	if (ft_init_sprite(info))
//		return (ft_free(info), 1);
	return (0);
}
