/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 20:51:28 by fmehdaou          #+#    #+#             */
/*   Updated: 2020/12/01 20:54:20 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

int		null_text(char *path)
{
	return ((path != NULL));
}

int		pngend(char *png)
{
	int		len;

	len = ft_strlen(png) - 1;
	return (png[len] == 'm'
		&& png[len - 1] == 'p'
		&& png[len - 2] == 'x'
		&& png[len - 3] == '.');
}

char	*ft_each_texture(char *path, t_cub3d *cub)
{
	int len;
	int fd;

	if (null_text(path))
		ft_errors(g_micub_err[DUP_LINE], g_micub_err[TEXTURE]);
	if (cub->getl.spaces > 0)
		ft_errors(g_micub_err[NOSPACESNEEDED], g_micub_err[TEXTURE]);
	len = ft_len(cub->getl.newline);
	if (len != 2)
		ft_errors(g_micub_err[NUM_ARG], g_micub_err[TEXTURE]);
	else if ((fd = open(cub->getl.newline[1], O_RDONLY)) == -1)
		ft_errors(g_micub_err[INVALID_PATH], g_micub_err[TEXTURE]);
	path = ft_strdup(cub->getl.newline[1]);
	if (!pngend(path))
		ft_errors(g_micub_err[EXTENSION], g_micub_err[MAP_FILE]);
	return (path);
}

void	ft_textures(t_cub3d *cub)
{
	int len;
	int fd;

	cub->getl.newline = ft_split(cub->getl.line, ' ');
	if (ft_strcmp(cub->getl.newline[0], "NO") == 0)
		cub->tex.north = ft_each_texture(cub->tex.north, cub);
	else if (ft_strcmp(cub->getl.newline[0], "SO") == 0)
		cub->tex.south = ft_each_texture(cub->tex.south, cub);
	else if (ft_strcmp(cub->getl.newline[0], "WE") == 0)
		cub->tex.west = ft_each_texture(cub->tex.west, cub);
	else if (ft_strcmp(cub->getl.newline[0], "EA") == 0)
		cub->tex.east = ft_each_texture(cub->tex.east, cub);
	else if (ft_strcmp(cub->getl.newline[0], "S") == 0)
		cub->tex.sprite = ft_each_texture(cub->tex.sprite, cub);
	else
		ft_errors(g_micub_err[INVALID_LINE], g_micub_err[TEXTURE]);
	ft_free(cub->getl.newline);
}
