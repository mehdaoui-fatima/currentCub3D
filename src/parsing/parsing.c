/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 19:57:40 by fmehdaou          #+#    #+#             */
/*   Updated: 2020/12/01 13:18:48 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	initializedata(t_cub3d *cub)
{
	cub->res.rx = -1;
	cub->res.ry = -1;
	cub->rgb.cr = -1;
	cub->rgb.cg = -1;
	cub->rgb.cb = -1;
	cub->rgb.fr = -1;
	cub->rgb.fg = -1;
	cub->rgb.fb = -1;
	cub->tex.north = NULL;
	cub->tex.east = NULL;
	cub->tex.west = NULL;
	cub->tex.south = NULL;
	cub->tex.sprite = NULL;
	cub->maps.map_len = 0;
	cub->posx = -1;
	cub->posy = -1;
	cub->numsprites = 0;
}

void	files_error(t_cub3d *cub, char *argv)
{
	int	arg;

	arg = ft_strlen(argv) - 1;
	if (!(argv[arg] == 'b' && argv[arg - 1] == 'u' && argv[arg - 2] == 'c'
	&& argv[arg - 3] == '.'))
		ft_errors(g_micub_err[FILE], g_micub_err[MAP_FILE]);
	if ((cub->getl.fd = open(argv, O_RDONLY)) < 0)
	{
		ft_putendl_fd("Error\n", 1);
		perror(strerror(errno));
		exit(0);
	}
}

int		empty_line(t_cub3d *cub)
{
	int res;

	res = 0;
	if (ft_strcmp(cub->getl.line, "\0") == 0)
	{
		free(cub->getl.line);
		cub->getl.line = NULL;
		res = 1;
	}
	return (res);
}

t_cub3d	*parsing(t_cub3d *cub, char *argv)
{
	char	r;

	files_error(cub, argv);
	initializedata(cub);
	while ((cub->getl.r = get_next_line(cub->getl.fd, &(cub->getl.line))) == 1)
	{
		if (empty_line(cub))
			continue;
		cub->getl.spaces = ft_spaces(cub);
		r = cub->getl.line[cub->getl.spaces];
		if (r == 'R')
			resolution(cub);
		else if (r == 'F' || r == 'C')
			ft_ceil_floor(cub);
		else if (r == 'N' || r == 'S' || r == 'W' || r == 'E')
			ft_textures(cub);
		else if (r == '1')
			ft_map(cub);
		else
			ft_errors(g_micub_err[IMPOSTER], g_micub_err[MAP_FILE]);
		free(cub->getl.line);
	}
	if (!ft_missingdata(cub) || !cub->maps.map)
		ft_errors(g_micub_err[MISSING], g_micub_err[MAP_FILE]);
	return (cub);
}
