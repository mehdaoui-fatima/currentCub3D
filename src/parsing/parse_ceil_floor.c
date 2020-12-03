/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ceil_floor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 11:17:19 by fmehdaou          #+#    #+#             */
/*   Updated: 2020/12/02 14:30:06 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

int		create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int		ft_check_commas(char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i + 1])
	{
		if (line[i] == ',' && line[i + 1] == ',')
			return (1);
		i++;
	}
	if (line[i] == ',' || line[0] == ',')
		return (1);
	return (0);
}

void	ft_each_color(int *r, int *g, int *b, t_cub3d *cub)
{
	if (*r != -1)
		ft_errors(g_micub_err[DUP_LINE], g_micub_err[cub->err.err]);
	*r = ft_atoi(cub->getl.new[0]);
	*g = ft_atoi(cub->getl.new[1]);
	*b = ft_atoi(cub->getl.new[2]);
	if (!((*r >= 0 && *r <= 255) &&
	(*g >= 0 && *g <= 255) && (*b >= 0 && *b <= 255)))
		ft_errors(g_micub_err[INVALID_RGB], g_micub_err[cub->err.err]);
}

void	get_color(int len1, int len2, t_cub3d *cub)
{
	cub->err.err = (cub->getl.newline[0][0] == 'C') ? CEILING : FLOOR;
	if (cub->getl.spaces > 0)
		ft_errors(g_micub_err[NOSPACESNEEDED], g_micub_err[cub->err.err]);
	if (len1 != 2 || len2 != 3)
		ft_errors(g_micub_err[NUM_ARG], g_micub_err[cub->err.err]);
	else if (!(ft_isnumber(cub->getl.new[0]) &&
	ft_isnumber(cub->getl.new[1]) && ft_isnumber(cub->getl.new[2])))
		ft_errors(g_micub_err[INVALID_RGB], g_micub_err[cub->err.err]);
	else if (ft_check_commas(cub->getl.newline[1]))
		ft_errors(g_micub_err[INVALID_RGB], g_micub_err[cub->err.err]);
	else if (cub->err.err == CEILING)
		ft_each_color(&cub->rgb.cr, &cub->rgb.cg,
		&cub->rgb.cb, cub);
	else if (cub->err.err == FLOOR)
		ft_each_color(&cub->rgb.fr, &cub->rgb.fg,
		&cub->rgb.fb, cub);
}

void	ft_ceil_floor(t_cub3d *cub)
{
	int		len1;
	int		len2;

	cub->getl.newline = ft_split(cub->getl.line, ' ');
	cub->getl.new = ft_split(cub->getl.newline[1], ',');
	len1 = ft_len(cub->getl.newline);
	len2 = ft_len(cub->getl.new);
	if ((ft_strcmp(cub->getl.newline[0], "C") == 0) ||
	(ft_strcmp(cub->getl.newline[0], "F") == 0))
		get_color(len1, len2, cub);
	else
		ft_errors(g_micub_err[INVALID_LINE], g_micub_err[MAP_FILE]);
	cub->rgb.ceilcolor = create_rgb(cub->rgb.cr, cub->rgb.cg, cub->rgb.cb);
	cub->rgb.floorcolor = create_rgb(cub->rgb.fr, cub->rgb.fg, cub->rgb.fb);
	ft_free(cub->getl.newline);
	ft_free(cub->getl.new);
}
