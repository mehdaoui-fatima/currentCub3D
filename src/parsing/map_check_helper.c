/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 20:47:56 by fmehdaou          #+#    #+#             */
/*   Updated: 2020/12/01 20:50:21 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	first_last_line(char *first, char *last)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (first[i] || last[j])
	{
		if (first[i])
		{
			if (first[i] != '1' && first[i] != ' ')
				ft_errors(g_micub_err[INVALID_MAP], g_micub_err[MAP]);
			i++;
		}
		else if (last[j])
		{
			if (last[j] != '1' && last[j] != ' ')
				ft_errors(g_micub_err[INVALID_MAP], g_micub_err[MAP]);
			j++;
		}
	}
}

void	ft_borders(char c1, char c2)
{
	if (c1 != '1' || c2 != '1')
		ft_errors(g_micub_err[INVALID_MAP], g_micub_err[MAP]);
}

int		ft_surrounded(char a, char b, char c, char d)
{
	return ((a == '1' || a == ' ')
	&& (b == '1' || b == ' ') && (c == '1' || c == ' ')
	&& (d == '1' || d == ' '));
}

double	*create_dir_plan(double a, double b, double c, double d)
{
	double *tab;

	tab = (double*)malloc(sizeof(double) * 4);
	tab[0] = a;
	tab[1] = b;
	tab[2] = c;
	tab[3] = d;
	return (tab);
}

void	ft_dir_plan(t_cub3d *cub, double *tab)
{
	cub->dirx = tab[0];
	cub->diry = tab[1];
	cub->planx = tab[2];
	cub->plany = tab[3];
	free(tab);
}
