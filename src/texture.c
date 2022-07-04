/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 11:10:49 by ghanquer          #+#    #+#             */
/*   Updated: 2022/07/04 12:11:28 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char	*ft_strdup(const char *s)
{
	int		i;
	int		j;
	char	*str;

	j = 0;
	i = 0;
	while (s[i])
		i++;
	str = malloc(sizeof(char) * i + 1);
	if (!str)
		return (0);
	while (j < i)
	{
		str[j] = s[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*get_texture_path(void)
{
	return (ft_strdup("textures/wall.xpm"));
}

t_texture	get_texture(t_info *info)
{
	t_texture	my_texture;

	my_texture.path = get_texture_path();
	my_texture.img.img = mlx_xpm_file_to_image(info->mlx, my_texture.path,\
			&my_texture.width, &my_texture.height);
	if (!my_texture.img.img)
		return (printf("Impossible d'ouvrir la texture\n"), my_texture);
	my_texture.img.addr = mlx_get_data_addr(my_texture.img.img, &my_texture.img.bits_per_pixel, &my_texture.img.line_length, &my_texture.img.endian);
	return (my_texture);
}
