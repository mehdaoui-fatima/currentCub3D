/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 20:32:10 by fmehdaou          #+#    #+#             */
/*   Updated: 2020/12/01 20:46:05 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	get_compass(int i, t_cub3d *cub, char *str)
{
	if (str[i] == 'N')
		ft_dir_plan(cub, create_dir_plan(-1, 0, 0, 0.66));
	else if (str[i] == 'S')
		ft_dir_plan(cub, create_dir_plan(1, 0, 0, -0.66));
	else if (str[i] == 'W')
		ft_dir_plan(cub, create_dir_plan(0, -1, -0.66, 0));
	else if (str[i] == 'E')
		ft_dir_plan(cub, create_dir_plan(0, 1, 0.66, 0));
}

int		ft_each_map_line(char *str, int index, t_cub3d *cub)
{
	int tab[4];
	int i;
	int j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] != '2' && str[i] != '1' && str[i] != ' ' && str[i] != '0' &&
		str[i] != 'N' && str[i] != 'W' && str[i] != 'E' && str[i] != 'S')
			return (0);
		if (str[i] == 'N' || str[i] == 'W' || str[i] == 'E' || str[i] == 'S')
		{
			if (cub->posy != -1)
				ft_errors(g_micub_err[DIR], g_micub_err[MAP]);
			cub->posx = index + 0.1;
			cub->posy = i + 0.1;
			get_compass(i, cub, str);
		}
		if (str[i] == '2')
			cub->numsprites++;
	}
	return (1);
}

void	space_found(t_var *var, t_cub3d *cub)
{
	if (0 <= var->j - 1 && var->j - 1 <= var->len_j)
		var->a = cub->maps.new_map[var->i][var->j - 1];
	if (0 <= var->j + 1 && var->j + 1 <= var->len_j)
		var->c = cub->maps.new_map[var->i][var->j + 1];
	if (0 <= var->i - 1 && var->i - 1 <= var->len_i)
	{
		var->len_previous = ft_strlen(cub->maps.new_map[var->i - 1]) - 1;
		if (var->len_previous < var->j)
			var->b = '1';
		else
			var->b = cub->maps.new_map[var->i - 1][var->j];
	}
	if (0 <= var->i + 1 && var->i + 1 <= var->len_i)
	{
		var->len_next = ft_strlen(cub->maps.new_map[var->i + 1]) - 1;
		if (var->len_next < var->j)
			var->d = '1';
		else
			var->d = cub->maps.new_map[var->i + 1][var->j];
	}
	if (!ft_surrounded(var->a, var->b, var->c, var->d))
		ft_errors(g_micub_err[INVALID_MAP], g_micub_err[MAP]);
}

void	var_init(t_var *var)
{
	var->i = -1;
	var->a = '1';
	var->b = '1';
	var->c = '1';
	var->d = '1';
}

void	ft_mapvalid(t_cub3d *cub)
{
	t_var var;

	var_init(&var);
	if (cub->maps.index < 2)
		ft_errors(g_micub_err[INVALID_MAP], g_micub_err[MAP]);
	first_last_line(cub->maps.new_map[0], cub->maps.new_map[cub->maps.index]);
	while (cub->maps.new_map[++var.i])
	{
		var.str = ft_strtrim(cub->maps.new_map[var.i], " ");
		if (!ft_each_map_line(cub->maps.new_map[var.i], var.i, cub))
			ft_errors(g_micub_err[INVALID_MAP], g_micub_err[MAP]);
		var.len = ft_strlen(var.str) - 1;
		ft_borders(var.str[0], var.str[var.len]);
		var.len_j = ft_strlen(cub->maps.new_map[var.i]) - 1;
		var.len_i = cub->maps.index;
		free(var.str);
		var.str = NULL;
		var.j = -1;
		while (cub->maps.new_map[var.i][++var.j])
			if (cub->maps.new_map[var.i][var.j] == ' ')
				space_found(&var, cub);
	}
	cub->zbuffer = (double*)malloc(sizeof(double) * cub->res.rx);
	cub->sprites = (t_sprite*)malloc(sizeof(t_sprite) * cub->numsprites);
	ft_create_worldmap(cub);
}
