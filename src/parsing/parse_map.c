/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 13:51:23 by fmehdaou          #+#    #+#             */
/*   Updated: 2020/12/01 13:59:32 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

int		ft_missingdata(t_cub3d *cub)
{
	return (
		(cub->res.rx != -1 && cub->res.ry != -1) &&
		(cub->rgb.cr != -1 && cub->rgb.cg != -1 && cub->rgb.cb != -1) &&
		(cub->rgb.fr != -1 && cub->rgb.fg != -1 && cub->rgb.fb != -1) &&
		(cub->tex.north != NULL && cub->tex.south != NULL &&
		cub->tex.west != NULL && cub->tex.east != NULL
		&& cub->tex.sprite != NULL));
}

void	ft_addrow(t_cub3d *cub)
{
	int res;

	cub->maps.tmp = (char**)malloc(
		(cub->maps.map_len = ft_len(cub->maps.map) + 2) * sizeof(char*));
	cub->maps.index = -1;
	while (cub->maps.map[++cub->maps.index])
		cub->maps.tmp[cub->maps.index] =
		ft_strdup(cub->maps.map[cub->maps.index]);
	cub->maps.tmp[cub->maps.index] = ft_strdup(cub->getl.line);
	cub->maps.tmp[cub->maps.index + 1] = NULL;
	cub->maps.max_len =
	(cub->maps.max_len < (res = ft_strlen(cub->getl.line)))
	? res : cub->maps.max_len;
	ft_free(cub->maps.map);
	cub->maps.map = cub->maps.tmp;
	free(cub->getl.line);
	cub->getl.line = NULL;
}

void	ft_map(t_cub3d *cub)
{
	int true;
	int i;

	true = 1;
	i = 3;
	if (!ft_missingdata(cub))
		ft_errors(g_micub_err[INVALID_LINE], g_micub_err[MAP_FILE]);
	if (true)
	{
		cub->maps.map = (char **)malloc(2 * sizeof(char *));
		cub->maps.map[0] = ft_strdup(cub->getl.line);
		cub->maps.max_len = ft_strlen(cub->getl.line);
		cub->maps.map[1] = NULL;
		true = 0;
		free(cub->getl.line);
	}
	while ((cub->getl.r = get_next_line(cub->getl.fd, &(cub->getl.line))) == 1)
		ft_addrow(cub);
	ft_addrow(cub);
	ft_new_map(cub);
	ft_mapvalid(cub);
	if (cub->posy == -1)
		ft_errors(g_micub_err[MISSING], g_micub_err[MAP]);
}
