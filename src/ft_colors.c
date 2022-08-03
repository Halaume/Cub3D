/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:35:28 by nflan             #+#    #+#             */
/*   Updated: 2022/08/03 17:51:24 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	ft_check_colors(char **tab)
{
	if (ft_tablen(tab) != 3)
		return (0);
	if (ft_atoi(tab[0]) < 0 || ft_atoi(tab[0]) > 255)
		return (0);
	if (ft_atoi(tab[1]) < 0 || ft_atoi(tab[1]) > 255)
		return (0);
	if (ft_atoi(tab[2]) < 0 || ft_atoi(tab[2]) > 255)
		return (0);
	return (1);
}

int	ft_fill_color(int *tofill, char *buf)
{
	char	*tofree;
	char	**tabtf;

	tofree = ft_strtrim(buf, " \n");
	if (!tofree)
		return (1);
	tabtf = ft_split(tofree, ',');
	free(tofree);
	if (!tabtf)
		return (1);
	if (ft_check_colors(tabtf))
		*tofill = create_trgb(100, (int)ft_atoi(tabtf[0]),
				(int)ft_atoi(tabtf[1]), (int)ft_atoi(tabtf[2]));
	else
		return (ft_free_split(tabtf), 3);
	return (ft_free_split(tabtf), 0);
}
