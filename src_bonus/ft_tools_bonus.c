/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 16:41:52 by nflan             #+#    #+#             */
/*   Updated: 2022/08/05 12:10:52 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

int	ft_poserr(int y, int x, char *str)
{
	char	*pos;

	pos = NULL;
	ft_putstr_error("Error\n");
	ft_putstr_error(str);
	pos = ft_itoa(x);
	if (!pos)
		return (1);
	ft_putstr_error("colonne ");
	ft_putstr_error(pos);
	free(pos);
	ft_putstr_error(" ligne ");
	pos = ft_itoa(y);
	if (!pos)
		return (1);
	ft_putstr_error(pos);
	free(pos);
	ft_putstr_error("\n");
	return (1);
}

int	ft_putstr_error(char *error)
{
	if (error)
		while (*error)
			write(2, (void *)error++, 1);
	return (1);
}

int	ft_putstr_frror(char *error, char *str, int i)
{
	char	*tofree;
	char	*tofree2;

	tofree = error;
	tofree2 = str;
	if (str && error)
		error = ft_strjoin(error, str);
	ft_putstr_error(error);
	if (i && i != 2)
		free(tofree);
	if (i && i != 1)
		free(tofree2);
	free(error);
	return (1);
}

int	ft_perror(char *error, char *str)
{
	if (str)
		error = ft_strjoin(error, str);
	if (!error)
		perror("Failed to malloc error msg");
	else
		perror(error);
	if (str)
		free(error);
	return (1);
}

int	ft_perror_free(char *error, char *str, int i)
{
	char	*tofree;
	char	*tofree2;

	tofree = error;
	tofree2 = str;
	if (str && error)
		error = ft_strjoin(error, str);
	perror(error);
	if (i != 2)
		free(tofree);
	if (i != 1)
		free(tofree2);
	free(error);
	return (1);
}
